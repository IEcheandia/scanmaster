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
    property int parameterValue: errorConfigModel && currentIndex != -1 ? errorConfigModel.data(errorConfigModel.index(currentIndex, 0)) : 0
    property var defaultValue: undefined
    property alias errorConfigModel: control.model
    property int enumValue: parameter ? parameter.value : (attribute ? attribute.defaultValue : -1)
    property int defaultIndex: errorConfigModel && defaultValue !== undefined ? errorConfigModel.indexForResultType(control.defaultValue).row : -1

    /**
     * Index is mapped from enum value.
     **/
    currentIndex: errorConfigModel ? errorConfigModel.indexForResultType(control.enumValue).row : -1
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
        if (control.errorConfigModel === undefined)
        {
            return;
        }
        if (control.defaultValue === undefined)
        {
            return;
        }
        control.errorConfigModel.ensureItemExists(control.defaultValue);
    }

    function checkParameterValue()
    {
        if (control.errorConfigModel === undefined)
        {
            return;
        }
        if (!control.parameter)
        {
            return;
        }
        control.errorConfigModel.ensureItemExists(control.parameter.value);
    }

    onDefaultValueChanged: checkDefaultValue()
    onParameterChanged: checkParameterValue()
    onErrorConfigModelChanged: {
        checkDefaultValue();
        checkParameterValue();
    }

    ToolTip.text: attribute ? LanguageSupport.getStringWithFallback(attribute.description) : ""
    ToolTip.visible: hovered && ToolTip.text != ""
    ToolTip.timeout: 5000
}
