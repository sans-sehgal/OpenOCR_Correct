#include "DiffView.h"
#include "ui_DiffView.h"
#include "diff_match_patch.h"
#include <string>
#include <qstring.h>
#include <Project.h>
#include <QMessageBox>

DiffView::DiffView(QWidget *parent, QString page,QString fpath)
	: QMainWindow(parent)
{
    pageNo = page.toStdString();
    gDirTwoLevelUp=fpath;
    ui = new Ui::DiffView();
    ui->setupUi(this);
    setWindowTitle("Verifier Output Difference " + page);


    //!check if file exists
    QFile fverifier(gDirTwoLevelUp+ "/VerifierOutput/"+ page );

     if(fverifier.exists())
     {
       Load_comparePage(page.toStdString());
       UpdateUI();
     }
     else{
          QMessageBox::information(0, "Error", "File Doesn't Exist");
     }
}

DiffView::~DiffView()
{
	delete ui;
}

void DiffView::Load_comparePage(string page)
{
    QString qs1="", qs2="",qs3="";
    QMessageBox msgBox;

    //! Open a Verifier's Output File
    QString file = gDirTwoLevelUp + "/VerifierOutput/" + QString::fromStdString(page);

    //! Opens corresponding Corrector's Output and OCR text file
    if(!file.isEmpty())
    {
        QString verifierText = file;
        QString correctorText = file.replace("VerifierOutput","CorrectorOutput"); //CAN CHANGE ACCORDING TO FILE STRUCTURE
        QString ocrText = file.replace("CorrectorOutput","Inds"); //CAN CHANGE ACCORDING TO FILE STRUCTURE
        ocrText.replace(".html",".txt");

        //! Reads OCR text file
        if(!ocrText.isEmpty())
        {
            QFile sFile(ocrText);
            if(sFile.open(QFile::ReadOnly | QFile::Text))
            {
                QTextStream in(&sFile);
                in.setCodec("UTF-8");
                qs1 = in.readAll().replace(" \n","\n");

                //! Displays an error if OCR text file is empty
                if(qs1=="")
                {
                    msgBox.setText("Error in Displaying File: "+ ocrText + "is Empty");
                    msgBox.exec();
                    return;
                }
                sFile.close();
            }
        }

        //! Reads Corrector's Output file
        if(!correctorText.isEmpty())
        {
            QFile sFile(correctorText);
            if(sFile.open(QFile::ReadOnly | QFile::Text))
            {
                QTextStream in(&sFile);
                in.setCodec("UTF-8");
                qs2 = in.readAll();

                //! Displays an error if Corrector's Output file is empty
                if(qs2=="")
                {
                    msgBox.setText("Error in Displaying File: "+ correctorText + "is Empty");
                    msgBox.exec();
                    return;
                }
                sFile.close();
            }
        }

        //! Reads Verifier's Output file
        if(!verifierText.isEmpty())
        {
            QFile sFile(verifierText);
            if(sFile.open(QFile::ReadOnly | QFile::Text))
            {
                QTextStream in(&sFile);
                in.setCodec("UTF-8");
                qs3 = in.readAll();

                 //! Displays an error if Verifier's Output file is empty
                if(qs3=="")
                {
                    msgBox.setText("Error in Displaying File: "+ verifierText + "is Empty");
                    msgBox.exec();
                    return;
                }
                sFile.close();
            }
        }

        QTextDocument doc;

        doc.setHtml(qs2);
        qs2 = doc.toPlainText().replace(" \n","\n");

        doc.setHtml(qs3);
        qs3 = doc.toPlainText().replace(" \n","\n");

        int l1,l2,l3, DiffOcr_Corrector,DiffCorrector_Verifier,DiffOcr_Verifier;
        float ocrErrorPerc;

        l1 = mProject.GetGraphemesCount(qs1); l2 = mProject.GetGraphemesCount(qs2); l3 = mProject.GetGraphemesCount(qs3);

        diff_match_patch dmp;

        //! Calculates the percentage of changes made by the corrector in OCR text file
        auto diffs1 = dmp.diff_main(qs1,qs2);
        DiffOcr_Corrector = mProject.LevenshteinWithGraphemes(diffs1);
        correctorChangesPerc = ((float)(DiffOcr_Corrector)/(float)l2)*100;
        if(correctorChangesPerc>100) correctorChangesPerc = ((float)(DiffOcr_Corrector)/(float)l1)*100;
        correctorChangesPerc = (((float)lround(correctorChangesPerc*100))/100);

        //! Calculates the percentage of changes made by the verifier in Corrector's Output file
        auto diffs2 = dmp.diff_main(qs2,qs3);
        DiffCorrector_Verifier = mProject.LevenshteinWithGraphemes(diffs2);
        verifierChangesPerc = ((float)(DiffCorrector_Verifier)/(float)l3)*100;
        if(verifierChangesPerc>100) verifierChangesPerc = ((float)(DiffCorrector_Verifier)/(float)l2)*100;
        verifierChangesPerc = (((float)lround(verifierChangesPerc*100))/100);

        //! Calculates the accuracy of OCR text w.r.t. Verified text
        auto diffs3 = dmp.diff_main(qs1,qs3);
        DiffOcr_Verifier = mProject.LevenshteinWithGraphemes(diffs3);
        ocrErrorPerc = ((float)(DiffOcr_Verifier)/(float)l3)*100;
        if(ocrErrorPerc>100) ocrErrorPerc = ((float)(DiffOcr_Verifier)/(float)l1)*100;
        OcrAcc = 100 - (((float)lround(ocrErrorPerc*100))/100);

        doc.setHtml(qs1);
        QString interntext = doc.toPlainText();

        doc.setHtml(qs2);
        QString ocrtext = doc.toPlainText();

        doc.setHtml(qs3);
        QString verifiertext = doc.toPlainText();

        auto diffs = dmp.diff_main(ocrtext,interntext);
        QString textcolor = "ffd13d";
        QList<QString> htmlList1 = dmp.diff_prettyHtml(diffs, textcolor);
        html1 = htmlList1.first();
        html2 = htmlList1.last();

        diffs = dmp.diff_main(interntext,verifiertext);
        textcolor = "90ff90";
        QList<QString> htmlList2 = dmp.diff_prettyHtml(diffs, textcolor);
        html3 = htmlList2.first();
        html1.remove("&para;");
        html2.remove("&para;");
        html3.remove("&para;");
        QString title = "Compare Verifier Output " + QString::fromStdString(page) ;
        setWindowTitle(title);
     }
}

void DiffView::UpdateUI()
{
    ui->InternText->setHtml(html1);
    ui->OCRText->setHtml(html2);
    ui->VerifierText->setHtml(html3);

    //!Updating calculated percentages into UI
    QString corrChanges = QString::number(correctorChangesPerc,'f',2) + "%";
    ui->InternLabel->setText("<b><p>2. Corrector's Output Text</b></p>Changes Made by Corrector:  " + corrChanges);

    QString VerifierLabel = QString::number(verifierChangesPerc,'f',2) + "%";
    ui->VerifierLabel->setText("<p><b>3. Verified Text</b></p>Changes Made by Verifier: " + VerifierLabel);

    QString OCRLabel = QString::number(OcrAcc,'f',2) + "%";
    ui->OCRLabel->setText("<p><b>1. Initial Text </b></p>Accuracy of OCR Text (w.r.t Verified Text): " +OCRLabel);
}

void DiffView::on_PrevButton_clicked()
{
    //! Extract page number from the localFilename
    string no = "";
    size_t loc;
    QString ext = "";
    if(!mProject.GetPageNumber(pageNo, &no, &loc, &ext))
        return;

    if(stoi(no)-1>0)   //to avoid negative page numbers
     {
        //!check if file exists
        string pages = pageNo;
        pages.replace(loc,no.size(),to_string(stoi(no) - 1));
        QFile fverifier(gDirTwoLevelUp+ "/VerifierOutput/"+ QString::fromStdString(pages) );

         if(fverifier.exists())
         {
           pageNo.replace(loc,no.size(),to_string(stoi(no) - 1)); //Decrement the page number
           Load_comparePage(pageNo);
           UpdateUI();
         }
         else{
             return ;
         }
     }
}

void DiffView::on_NextButton_clicked()
{
    //! Extract page number from the localFilename
    string no = "";
    size_t loc;
    QString ext = "";
    if(!mProject.GetPageNumber(pageNo, &no, &loc, &ext))
        return;
    //!check if file exists
    string pages = pageNo;
    pages.replace(loc,no.size(),to_string(stoi(no) + 1));
    QFile fverifier(gDirTwoLevelUp+ "/VerifierOutput/"+ QString::fromStdString(pages) );

     if(fverifier.exists())
     {
       pageNo.replace(loc,no.size(),to_string(stoi(no) + 1)); //Increment the page number
       Load_comparePage(pageNo);
       UpdateUI();
     }
     else{
         return ;
     }
}

