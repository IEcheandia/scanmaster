import QtQuick 2.5
import QtQuick.Controls 2.3
import precitec.gui.components.application 1.0 as PrecitecApplication

import Precitec.AppGui 1.0
import precitec.gui.general 1.0

/**
 * ComboBox taking values from an attribute representing a sensor
 * and the value from a parameter.
 **/
ComboBox {
    id: control
    /**
     * Emitted when a combobox element gets activated.
     **/
    signal parameterValueModified()

    property var attribute: null
    property var parameter: null
    property int parameterValue: sensorConfigModel && currentIndex != -1 ? sensorConfigModel.data(sensorConfigModel.index(currentIndex, 0)) : 0
    property var defaultValue: undefined
    property alias sensorConfigModel: control.model
    property int enumValue: parameter ? parameter.value : (attribute ? attribute.defaultValue : -1)
    property int defaultIndex: sensorConfigModel && defaultValue !== undefined ? sensorConfigModel.indexForResultType(control.defaultValue).row : -1

    /**
     * Index is mapped from enum value.
     **/
    currentIndex: sensorConfigModel ? sensorConfigModel.indexForResultType(control.enumValue).row : -1
    onActivated: parameterValueModified()

    delegate: ItemDelegate {
        id: delegate
        function updateImplicitWidth()
        {
            if (delegate.implicitWidth > control.popup.width)
            {
                control.popup.width = delegate.implicitWidth
            }
        }
        width: control.popup.width
        contentItem: Label {
            id: label
            font.weight: control.currentIndex === index ? Font.DemiBold : Font.Normal
            font.italic: control.defaultIndex == index
            text: model.name + " (" + model.enumType + ")" + (control.defaultIndex == index ? " (" + qsTr("Default") + ")" : "")
        }
        highlighted: control.highlightedIndex === index
        onImplicitWidthChanged: updateImplicitWidth()
        Component.onCompleted: updateImplicitWidth()
    }
    textRole: "name"
    palette.buttonText: control.currentIndex != control.defaultIndex ? PrecitecApplication.Settings.text : (ApplicationWindow.window ? ApplicationWindow.window.palette.buttenText : "black")

    function checkDefaultValue()
    {
        if (control.sensorConfigModel === undefined)
        {
            return;
        }
        if (control.defaultValue === undefined)
        {
            return;
        }
        control.sensorConfigModel.ensureItemExists(control.defaultValue);
    }

    function checkParameterValue()
    {
        if (control.sensorConfigModel === undefined)
        {
            return;
        }
        if (!control.parameter)
        {
            return;
        }
        control.sensorConfigModel.ensureItemExists(control.parameter.value);
    }

    onDefaultValueChanged: checkDefaultValue()
    onParameterChanged: checkParameterValue()
    onSensorConfigModelChanged: {
        checkDefaultValue();
        checkParameterValue();
    }

    ToolTip.text: attribute ? LanguageSupport.getStringWithFallback(attribute.description) : ""
    ToolTip.visible: hovered && ToolTip.text != ""
    ToolTip.timeout: 5000
}
