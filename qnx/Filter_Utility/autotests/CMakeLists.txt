set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set (LIBS   Qt5::Test
            Qt5::Core
            ${POCO_LIBS}
            fliplib
            Interfaces
            Analyzer_Interface)

qtTestCase(
    NAME
        testSystemConstant
    SRCS
        systemConstantTest.cpp
        ../systemConstant.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testConditional
    SRCS
        conditionalTest.cpp
        ../conditional.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testArithmeticConstant
    SRCS
        arithmeticConstantTest.cpp
        ../arithmeticConstant.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testArithmeticConstant_WithQueue
    SRCS
        arithmeticConstant_WithQueue_Test.cpp
        ../arithmeticConstant.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testArithmeticConstant_WithArray
    SRCS
        arithmeticConstant_WithArray_Test.cpp
        ../arithmeticConstant.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testArithmetic
    SRCS
        arithmeticTest.cpp
        ../arithmetic.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testBuffer
    SRCS
        bufferTest.cpp
        ../bufferRecorder.cpp
        ../bufferPlayer.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testContourBuffer
    SRCS
        contourBufferTest.cpp
        ../ContourBufferRecorder.cpp
        ../ContourBufferPlayer.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)


testCase(
    NAME
        testGenerateArcContour
    SRCS
        generateArcContourTest.cpp
        ../generateArcContour.cpp
    LIBS
        Qt5::Test
        Qt5::Core
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testContextNormalizeDouble
    SRCS
        contextNormalizeDoubleTest.cpp
        ../contextNormalizeDouble.cpp
    LIBS
        fliplib
        Interfaces
        Analyzer_Interface
)

testCase(
    NAME
        testGenerateContour
    SRCS
        generateContourTest.cpp
        ../generateContour.cpp
    LIBS
        Qt5::Test
        Qt5::Core
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

testCase(
    NAME
        testContourFromFile
    SRCS
        contourFromFileTest.cpp
        ../contourFromFile.cpp
        ../ramping.cpp
    LIBS
        Qt5::Test
        Qt5::Core
        ${POCO_LIBS}
        fliplib
        Interfaces

)

testCase(
    NAME
        testRotateContour
    SRCS
        rotateContourTest.cpp
        ../rotateContour.cpp
    LIBS
        Qt5::Test
        Qt5::Core
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

testCase(
    NAME
        testConditionalLine
    SRCS
        testConditionalLine.cpp
        ../conditionalLine.cpp
    LIBS
        Qt5::Test
        Qt5::Core
        ${POCO_LIBS}
        fliplib
        Interfaces
)

testCase(
    NAME
        testValueDisplay
    SRCS
        testValueDisplay.cpp
        ../valueDisplay.cpp
    LIBS
        Qt5::Test
        Qt5::Core
        ${POCO_LIBS}
        fliplib
        Interfaces
)

testCase(
    NAME
        testConditionalContour
    SRCS
        conditionalContourTest.cpp
        ../conditionalContour.cpp
    LIBS
        Qt5::Test
        Qt5::Core
        ${POCO_LIBS}
        fliplib
        Interfaces
)

testCase(
    NAME
        testPoorPenetrationCheckerTriple
    SRCS
        poorPenetrationCheckerTripleTest.cpp
        ../poorPenetrationCheckerTriple.cpp
        ../poorPenetrationPaint.cpp
    LIBS
        Qt5::Test
        Qt5::Core
        ${POCO_LIBS}
        fliplib
        Interfaces
)

testCase(
    NAME
        testDataSubsampling
    SRCS
        dataSubsamplingTest.cpp
        ../dataSubsampling.cpp
        ../dataSubsampling2.cpp
    LIBS
        Qt5::Test
        Qt5::Core
        ${POCO_LIBS}
        fliplib
        Interfaces
)

testCase(
    NAME
        testContourPathLocation
    SRCS
        testContourPathLocation.cpp
    LIBS
        ${LIBS}
)

testCase(
    NAME
        testRamping
    SRCS
        rampingTest.cpp
        ../ramping.cpp
    LIBS
        Qt5::Test
        Qt5::Core
)

qtTestCase(
    NAME
        testIntersect2Lines
    SRCS
        intersect2LinesTest.cpp
        ../intersect2Lines.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testHardwareParameter
    SRCS
        hardwareParameterTest.cpp
        ../hardwareParameter.cpp
        ../../Filtertest/dummyLogger.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
        Mod_Analyzer
)

qtTestCase(
    NAME
        testSpeedCompensation
    SRCS
        speedCompensationTest.cpp
        ../speedCompensation.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)

qtTestCase(
    NAME
        testTemporalLowPass
    SRCS
        testTemporalLowPass.cpp
        ../temporalLowPass.cpp
        ../temporalLowPass2.cpp
    LIBS
        ${POCO_LIBS}
        fliplib
        Interfaces
        Analyzer_Interface
)
