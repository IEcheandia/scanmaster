import QtQuick 2.5
import QtQuick.Controls 2.3
import precitec.gui.components.application 1.0 as PrecitecApplication

import Precitec.AppGui 1.0
import precitec.gui.general 1.0

/**
 * ComboBox taking values from an attribute representing a result
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
    property int parameterValue: resultsConfigFilterModel && currentIndex != -1 ? resultsConfigFilterModel.sourceModel.data(resultsConfigFilterModel.mapToSource(resultsConfigFilterModel.index(currentIndex, 0))) : 0
    property var defaultValue: undefined
    property alias resultsConfigFilterModel: control.model
    property int enumValue: parameter ? parameter.value : (attribute ? attribute.defaultValue : -1)
    property int defaultIndex: resultsConfigFilterModel && defaultValue !== undefined ? resultsConfigFilterModel.mapFromSource(resultsConfigFilterModel.sourceModel.indexForResultType(control.defaultValue)).row : -1

    /**
     * Index is mapped from enum value.
     **/
    currentIndex: resultsConfigFilterModel ? resultsConfigFilterModel.mapFromSource(resultsConfigFilterModel.sourceModel.indexForResultType(control.enumValue)).row : -1
    onActivated: parameterValueModified()

    delegate: ItemDelegate {
        width: control.width
        contentItem: Label {
            id: label
            font.weight: control.currentIndex === index ? Font.DemiBold : Font.Normal
            font.italic: control.defaultIndex == index
            text: model.name + " (" + model.enumType + ")" + (control.defaultIndex == index ? " (" + qsTr("Default") + ")" : "")
        }
        highlighted: control.highlightedIndex === index
    }
    textRole: "name"
    palette.buttonText: control.currentIndex != control.defaultIndex ? PrecitecApplication.Settings.text : (ApplicationWindow.window ? ApplicationWindow.window.palette.buttenText : "black")

    function checkDefaultValue()
    {
        if (control.resultsConfigFilterModel === undefined)
        {
            return;
        }
        if (control.defaultValue === undefined)
        {
            return;
        }
        control.resultsConfigFilterModel.sourceModel.ensureItemExists(control.defaultValue);
    }

    function checkParameterValue()
    {
        if (control.resultsConfigFilterModel === undefined)
        {
            return;
        }
        if (!control.parameter)
        {
            return;
        }
        control.resultsConfigFilterModel.sourceModel.ensureItemExists(control.parameter.value);
    }

    onDefaultValueChanged: checkDefaultValue()
    onParameterChanged: checkParameterValue()
    onResultsConfigFilterModelChanged: {
        checkDefaultValue();
        checkParameterValue();
    }

    ToolTip.text: attribute ? LanguageSupport.getStringWithFallback(attribute.description) : ""
    ToolTip.visible: hovered && ToolTip.text != ""
    ToolTip.timeout: 5000
}
