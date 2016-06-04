#include "productform.h"
#include "ui_productform.h"

ProductForm::ProductForm( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::ProductForm )
{
    ui->setupUi( this );
    _productModel = QSharedPointer<ProductModel>( new ProductModel() );
    setCategories();
    setSoldProductModel();

    connect( ui->pushButtonSearch
             , SIGNAL( clicked( bool ) )
             , SLOT( search() ) );
}


void ProductForm::closeEvent( QCloseEvent *event )
{
    emit closeProductForm();
    QWidget::closeEvent( event );
}


void ProductForm::setCategories()
{
    auto categories = _productModel->getCategoryList();
    categories.push_front( tr( "Всі" ) );

    ui->comboBoxCategory->addItems( categories );
}


void ProductForm::search()
{
    QString category = ui->comboBoxCategory->currentText();
    QString lowCost = ui->lineLowCost->text();
    QString hightCost = ui->lineHightCost->text();
    bool isCostEnable = ( !lowCost.isEmpty() || !hightCost.isEmpty() );

    if ( ( category != tr( "Всі" ) ) && isCostEnable ) {
        setSoldProductModelByCategoryAndCost( category );
    }
    else if ( category != tr( "Всі" ) ) {
        setSoldProductModelByCategory( category );
    }
    else if ( isCostEnable ) {
        setSoldProductModelByCost();
    }
    else {
        setSoldProductModel();
    }
}


void ProductForm::setProductModel()
{
    ui->tableProducts->setProductModel();
}


void ProductForm::setProductModel( QString orderId )
{
    ui->tableProducts->setProductModel( orderId );
}


void ProductForm::setSoldProductModel()
{
    ui->tableProducts->setSoldProductModel();
}


void ProductForm::setSoldProductModelByCategory( QString category )
{
    ui->tableProducts->setSoldProductModelByCategory( category );
}


void ProductForm::setSoldProductModelByCost()
{
    QString lowCost = !ui->lineLowCost->text().isEmpty()
                      ? ui->lineLowCost->text()
                      : QString::number( 0 );

    QString hightCost = !ui->lineHightCost->text().isEmpty()
                        ? ui->lineHightCost->text()
                        : QString::number( INT16_MAX );

    ui->tableProducts->setSoldProductModelByCost( lowCost, hightCost );
}


void ProductForm::setSoldProductModelByCategoryAndCost( QString category )
{
    QString lowCost = !ui->lineLowCost->text().isEmpty()
                      ? ui->lineLowCost->text()
                      : QString::number( 0 );

    QString hightCost = !ui->lineHightCost->text().isEmpty()
                        ? ui->lineHightCost->text()
                        : QString::number( INT16_MAX );

    QMap<QString, QString> data;
    data[ "category" ] = category;
    data[ "lowCost" ] = lowCost;
    data[ "hightCost" ] = hightCost;

    ui->tableProducts->setSoldProductModelByCategoryAndCost( data );
}


ProductForm::~ProductForm()
{
    delete ui;
}
