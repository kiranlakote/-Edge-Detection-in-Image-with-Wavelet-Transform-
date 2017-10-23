#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;



namespace Img
{

/// <summary>
/// Summary for DlgFltSelect
///
/// WARNING: If you change the name of this class, you will need to change the
///          'Resource File Name' property for the managed resource compiler tool
///          associated with all .resx files this class depends on.  Otherwise,
///          the designers will not be able to interact properly with localized
///          resources associated with this form.
/// </summary>
public ref class DlgFltSelect : public System::Windows::Forms::Form
{

        String^ m_dir;

public:

        DlgFltSelect(void) {
                InitializeComponent();

                m_filter = new wchar_t[_MAX_PATH];
                wcscpy(m_filter, L"filters\\daub1.flt");
        }

        DlgFltSelect(String^ dir): m_dir(dir) {
                InitializeComponent();

                m_filter = new wchar_t[_MAX_PATH];
                swprintf(m_filter, L"%s\\%s", PtrToStringChars(m_dir), L"daub1.flt");                
        }


        String^ fltname;
        wchar_t *m_filter;
        int m_scales;
        int m_th;


private:
        System::Windows::Forms::Button^  okButton;
private:
        System::Windows::Forms::Button^  cancelButton;
private:
        System::Windows::Forms::TextBox^  scaletextBox;
private:
        System::Windows::Forms::TextBox^  thtextBox;
private: 
        System::Windows::Forms::Label^  label1;
private: 
        System::Windows::Forms::Label^  label2;
private:
        System::Windows::Forms::ListBox^  fltlistBox;




protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~DlgFltSelect() {
                if (components) {
                        delete components;
                }
                delete[] m_filter;
        }

private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        void InitializeComponent(void) {
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->fltlistBox = (gcnew System::Windows::Forms::ListBox());
			this->scaletextBox = (gcnew System::Windows::Forms::TextBox());
			this->thtextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// okButton
			// 
			this->okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->okButton->Location = System::Drawing::Point(184, 12);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(75, 23);
			this->okButton->TabIndex = 3;
			this->okButton->Text = L"Ok";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &DlgFltSelect::okButton_Click);
			// 
			// cancelButton
			// 
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->Location = System::Drawing::Point(184, 41);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(75, 23);
			this->cancelButton->TabIndex = 4;
			this->cancelButton->Text = L"Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &DlgFltSelect::cancelButton_Click);
			// 
			// fltlistBox
			// 
			this->fltlistBox->FormattingEnabled = true;
			this->fltlistBox->Location = System::Drawing::Point(12, 12);
			this->fltlistBox->Name = L"fltlistBox";
			this->fltlistBox->Size = System::Drawing::Size(152, 160);
			this->fltlistBox->Sorted = true;
			this->fltlistBox->TabIndex = 0;
			this->fltlistBox->SelectedIndexChanged += gcnew System::EventHandler(this, &DlgFltSelect::fltlistBox_SelectedIndexChanged);
			// 
			// scaletextBox
			// 
			this->scaletextBox->Location = System::Drawing::Point(183, 83);
			this->scaletextBox->Name = L"scaletextBox";
			this->scaletextBox->Size = System::Drawing::Size(38, 20);
			this->scaletextBox->TabIndex = 1;
			this->scaletextBox->Text = L"3";
			this->scaletextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// thtextBox
			// 
			this->thtextBox->Location = System::Drawing::Point(183, 109);
			this->thtextBox->Name = L"thtextBox";
			this->thtextBox->Size = System::Drawing::Size(38, 20);
			this->thtextBox->TabIndex = 2;
			this->thtextBox->Text = L"20";
			this->thtextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(227, 86);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(32, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"scale";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(227, 112);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(22, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"TH";
			// 
			// DlgFltSelect
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(278, 194);
			this->ControlBox = false;
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->thtextBox);
			this->Controls->Add(this->scaletextBox);
			this->Controls->Add(this->fltlistBox);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->okButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"DlgFltSelect";
			this->Opacity = 0.85;
			this->Text = L"FWT filter select";
			this->Shown += gcnew System::EventHandler(this, &DlgFltSelect::DlgFltSelect_Shown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
        ////////////////////////////////////////////////////


        ////////////////////////////////////////////////////
private:
        System::Void fltlistBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
                fltname = fltlistBox->SelectedItem->ToString();
                swprintf(m_filter, L"%s\\%s", PtrToStringChars(m_dir), PtrToStringChars(fltlistBox->SelectedItem->ToString()));
        }

private:
        System::Void DlgFltSelect_Shown(System::Object^  sender, System::EventArgs^  e) {
                DirectoryInfo^ di = gcnew DirectoryInfo(m_dir);
                array < FileInfo^ >^ fi = di->GetFiles("*.flt");

                for (int i = 0; i < fi->Length; i++) {
                        FileInfo^ pfi = safe_cast < FileInfo^ > (fi->GetValue(i));
                        fltlistBox->Items->Add(pfi->Name);
                }

                scaletextBox->Text = m_scales.ToString();
                thtextBox->Text = m_th.ToString();
        }

private:
        System::Void okButton_Click(System::Object^  sender, System::EventArgs^  e) {
                m_scales = Convert::ToInt32(scaletextBox->Text);
                m_th = Convert::ToInt32(thtextBox->Text);
        }
private: System::Void cancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}
