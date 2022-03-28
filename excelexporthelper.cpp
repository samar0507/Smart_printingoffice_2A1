#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>

#include <QString>
#include <QFile>
#include <stdexcept>

using namespace std;

#include "excelexporthelper.h"

ExcelExportHelper::ExcelExportHelper(bool closeExcelOnExit)
{
    m_closeExcelOnExit = closeExcelOnExit;
    m_excelApplication = nullptr;
     m_cin= nullptr;
   m_nom= nullptr;
     m_prenom= nullptr;
    m_date= nullptr;
    m_adresse= nullptr;
    m_excelApplication = nullptr;

    m_excelApplication = new QAxObject( "Excel.Application", 0 );//{00024500-0000-0000-C000-000000000046}

    if (m_excelApplication == nullptr)
        throw invalid_argument("Failed to initialize interop with Excel (probably Excel is not installed)");

    m_excelApplication->dynamicCall( "SetVisible(bool)", false ); // hide excel
    m_excelApplication->setProperty( "DisplayAlerts", 0); // disable alerts

     m_cin = m_excelApplication->querySubObject( "cin" );
    m_nom =m_nom->querySubObject( "nom" );
    m_prenom = m_prenom->querySubObject( "prenom" );
    m_date=m_date->querySubObject( "date" );
    m_adresse=m_adresse->querySubObject( "Adresse" );

}

void ExcelExportHelper::SetCellValue(int lineIndex, int columnIndex, const QString& value)
{
    QAxObject *cell = m_adresse->querySubObject("Cells(int,int)", lineIndex, columnIndex);
    cell->setProperty("Value",value);
    delete cell;
}

void ExcelExportHelper::SaveAs(const QString& fileName)
{
    if (fileName == "")
        throw invalid_argument("'fileName' is empty!");
    if (fileName.contains("/"))
        throw invalid_argument("'/' character in 'fileName' is not supported by excel!");

    m_cin->dynamicCall("SaveAs (const QString&)", fileName);
}

ExcelExportHelper::~ExcelExportHelper()
{
    if (m_excelApplication != nullptr)
    {
        if (!m_closeExcelOnExit)
        {
            m_excelApplication->setProperty("DisplayAlerts", 1);
            m_excelApplication->dynamicCall("SetVisible(bool)", true );
        }

        if (m_cin != nullptr && m_closeExcelOnExit)
        {
            m_cin->dynamicCall("Close (Boolean)", true);
            m_excelApplication->dynamicCall("Quit (void)");
        }
    }

    delete m_cin;
    delete m_prenom;
    delete m_nom;
    delete m_date;
    delete m_adresse;
    delete m_excelApplication;
}
