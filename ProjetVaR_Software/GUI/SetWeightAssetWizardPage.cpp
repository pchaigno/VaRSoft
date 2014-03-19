#include "SetWeightAssetWizardPage.h"
#include "ui_SetWeightAssetWizardPage.h"

SetWeightAssetWizardPage::SetWeightAssetWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::SetWeightAssetWizardPage)
{
    ui->setupUi(this);
}

SetWeightAssetWizardPage::~SetWeightAssetWizardPage()
{
    delete ui;
}
/**
 * @brief SetWeightAssetWizardPage::initializePage
 * Load the formLayout with the list of the selected assets.
 */
void SetWeightAssetWizardPage::initializePage()
{
    QList<QString> listAssets = getAssetsSelected();
    foreach(QString str, listAssets)
    {
        QSpinBox* spinBox = new QSpinBox();
        weights[str]=spinBox;
        ui->weightFormLayout->addRow(str,spinBox);
    }
}
/**
 * @brief SetWeightAssetWizardPage::cleanupPage
 * Clear the formLayout
 */
void SetWeightAssetWizardPage::cleanupPage()
{
    weights.clear();
    clearLayout(ui->weightFormLayout);
}

/**
 * @brief SetWeightAssetWizardPage::clearLayout
 * Clear the specified layout.
 * @param layout The layout to clear.
 * @param deleteWidgets If true, it delete widgets in the layout, otherwise it just clear the layout without call delete on widgets. True by default.
 */
void SetWeightAssetWizardPage::clearLayout(QLayout* layout, bool deleteWidgets)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget())
                delete widget;
        }
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

/**
 * @brief SetWeightAssetWizardPage::getAssetsSelected
 * Retrieve the list of the assets selected in the previous page of the wizard.
 * @return QList of String
 */
QList<QString> SetWeightAssetWizardPage::getAssetsSelected() const
{
    return qobject_cast<ShowAssetsWizardPage *>(wizard()->page(wizard()->startId()))->getListAssetsSelected();
}

/**
 * @brief SetWeightAssetWizardPage::getWeights
 * Retrieve the weights entered by the user in a map.
 * @return a map with the weights associate to the name of the asset
 */
QMap<QString, int> SetWeightAssetWizardPage::getWeights() const
{
    QMap<QString, int>  res;
    foreach (const QString &str, weights.keys())
    {
        res[str]=weights.value(str)->value();
    }
    return res;
}

