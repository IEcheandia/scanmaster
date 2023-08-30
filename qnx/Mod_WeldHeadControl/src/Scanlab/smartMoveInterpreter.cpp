#include "viWeldHead/Scanlab/smartMoveInterpreter.h"

#include <iomanip>
#include <fstream>
#include <sys/mman.h>
#include <unistd.h>

namespace precitec
{
namespace hardware
{

SmartMoveInterpreter::SmartMoveInterpreter() = default;

SmartMoveInterpreter::~SmartMoveInterpreter()
{
    if (checkFileDescriptorExists(m_fileDescriptor))
    {
        close(m_fileDescriptor);
        m_fileDescriptor = -1;
    }
}

void SmartMoveInterpreter::setFilename(const std::string& filename)
{
    m_HPGL2Filename = filename;
}

int SmartMoveInterpreter::fileDescriptor() const
{
    if (!checkFileDescriptorExists(m_fileDescriptor))
    {
        return m_fileDescriptor;
    }
    auto returnValue = lseek(m_fileDescriptor, 0, SEEK_SET);
    if (returnValue == -1)          //lseek failed
    {
        return -1;
    }
    return m_fileDescriptor;
}

void SmartMoveInterpreter::setDebug(bool saveGeneratedFileToLogFolder)
{
    m_debug = saveGeneratedFileToLogFolder;
}

void SmartMoveInterpreter::newContour()
{
    m_currentContourHPGL2.clear();
    m_contourFileSize = 0;
    if (checkFileDescriptorExists(m_fileDescriptor))
    {
        close(m_fileDescriptor);
        m_fileDescriptor = -1;
    }
}

void SmartMoveInterpreter::createContourFile(const std::vector<std::shared_ptr<contour::Command>>& contourMetaLanguage)
{
    translateContour(contourMetaLanguage);
    writeAnonymousFile();

    if (m_debug)
    {
        saveHPGL2Contour();
    }
}

std::string SmartMoveInterpreter::translateInitialize()
{
    m_stringstream << std::string("IN") << ";";
    return m_stringstream.str();
}

std::string SmartMoveInterpreter::translateMark(double x, double y)
{
    m_stringstream << std::string("PD") << x << "," << y << ";";
    return m_stringstream.str();
}

std::string SmartMoveInterpreter::translateJump(double x, double y)
{
    m_stringstream << std::string("PU") << x << "," << y << ";";
    return m_stringstream.str();
}

std::string SmartMoveInterpreter::translateLaserPower(double power)
{
    m_stringstream << std::string("PW") << power << ";";
    return m_stringstream.str();
}

std::string SmartMoveInterpreter::translateMarkSpeed(double speed)
{
    m_stringstream << std::string("VS") << speed << ";";
    return m_stringstream.str();
}

void SmartMoveInterpreter::translateContour(const std::vector<std::shared_ptr<contour::Command>>& contourMetaLanguage)
{
    m_currentContourHPGL2.reserve(contourMetaLanguage.size());
    m_stringstream << std::setprecision(3) << std::fixed;

    for (const auto& element : contourMetaLanguage)
    {
        if (const auto initialize = std::dynamic_pointer_cast<contour::Initialize>(element))
        {
            m_currentContourHPGL2.push_back(translateInitialize());
        }
        else if (const auto mark = std::dynamic_pointer_cast<contour::Mark>(element))
        {
            m_currentContourHPGL2.push_back(translateMark(mark->x, mark->y));
        }
        else if (const auto jump = std::dynamic_pointer_cast<contour::Jump>(element))
        {
            m_currentContourHPGL2.push_back(translateJump(jump->x, jump->y));
        }
        else if (const auto laserPower = std::dynamic_pointer_cast<contour::LaserPower>(element))
        {
            m_currentContourHPGL2.push_back(translateLaserPower(laserPower->power));
        }
        else if (const auto markSpeed = std::dynamic_pointer_cast<contour::MarkSpeed>(element))
        {
            m_currentContourHPGL2.push_back(translateMarkSpeed(markSpeed->speed));
        }
        m_contourFileSize += m_currentContourHPGL2.back().size();
        m_stringstream.str("");
    }
}

int SmartMoveInterpreter::createAnonymousFileInMemory()
{
    std::string filename{"contour.txt"};
    return memfd_create(filename.c_str(), MFD_ALLOW_SEALING);
}

void SmartMoveInterpreter::writeAnonymousFile()
{
    if (m_currentContourHPGL2.empty() || m_contourFileSize == 0)
    {
        return;
    }

    m_fileDescriptor = createAnonymousFileInMemory();
    if (!checkFileDescriptorExists(m_fileDescriptor))
    {
        m_fileDescriptor = -1;
        return;
    }

    ftruncate(m_fileDescriptor, m_contourFileSize);

    for (const auto& command : m_currentContourHPGL2)
    {
        write(m_fileDescriptor, command.data(), command.size());
    }
}

bool SmartMoveInterpreter::checkFileDescriptorExists(int fileDescriptor) const
{
    return fileDescriptor != -1;
}

void SmartMoveInterpreter::saveHPGL2Contour()
{
    if (m_currentContourHPGL2.empty() || m_HPGL2Filename.empty())
    {
        return;
    }

    std::ofstream hpgl2File;
    hpgl2File.open(m_HPGL2Filename, std::ios::trunc);
    for (const auto& element : m_currentContourHPGL2)
    {
        hpgl2File << element << std::endl;
    }
    hpgl2File.close();
}

}
}
