
#pragma once

#include "fchildpic.h"


namespace Img
{


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for Form1
///
/// WARNING: If you change the name of this class, you will need to change the
///          'Resource File Name' property for the managed resource compiler tool
///          associated with all .resx files this class depends on.  Otherwise,
///          the designers will not be able to interact properly with localized
///          resources associated with this form.
/// </summary>
public ref class Form1 : public System::Windows::Forms::Form
{
public:
        Form1(void) {
                InitializeComponent();

                dir = IO::Directory::GetCurrentDirectory();
        }

        String^ dir;        //current directory

protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~Form1() {
                if (components) {
                        delete components;
                }
        }
private:
        System::Windows::Forms::MenuStrip^  mainMenu;
protected:
private:
        System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
private:
        System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
private:
        System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
private:
        System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
private:
        System::Windows::Forms::OpenFileDialog^  openPicDialog;





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
                System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
                this->mainMenu = (gcnew System::Windows::Forms::MenuStrip());
                this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
                this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->openPicDialog = (gcnew System::Windows::Forms::OpenFileDialog());
                this->mainMenu->SuspendLayout();
                this->SuspendLayout();
                //
                // mainMenu
                //
                this->mainMenu->Items->AddRange(gcnew cli::array < System::Windows::Forms::ToolStripItem^  > (1) {
                        this->fileToolStripMenuItem
                }
                                               );
                this->mainMenu->Location = System::Drawing::Point(0, 0);
                this->mainMenu->Name = L"mainMenu";
                this->mainMenu->Size = System::Drawing::Size(442, 24);
                this->mainMenu->TabIndex = 1;
                this->mainMenu->Text = L"mainMenu";
                //
                // fileToolStripMenuItem
                //
                this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array < System::Windows::Forms::ToolStripItem^  > (3) {
                        this->openToolStripMenuItem,
                        this->toolStripMenuItem1, this->exitToolStripMenuItem
                }
                                                                    );
                this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
                this->fileToolStripMenuItem->Size = System::Drawing::Size(35, 20);
                this->fileToolStripMenuItem->Text = L"&File";
                //
                // openToolStripMenuItem
                //
                this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
                this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
                this->openToolStripMenuItem->Size = System::Drawing::Size(166, 22);
                this->openToolStripMenuItem->Text = L"&Open ...";
                this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
                //
                // toolStripMenuItem1
                //
                this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
                this->toolStripMenuItem1->Size = System::Drawing::Size(163, 6);
                //
                // exitToolStripMenuItem
                //
                this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
                this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
                this->exitToolStripMenuItem->Size = System::Drawing::Size(166, 22);
                this->exitToolStripMenuItem->Text = L"E&xit";
                //
                // openPicDialog
                //
                this->openPicDialog->FileName = L"openPicDialog";
                this->openPicDialog->Filter = L"Image files|*.bmp;*.jpg;*.jpeg;*.png;*.tif;*.tiff";
                //
                // Form1
                //
                this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
                this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
                this->ClientSize = System::Drawing::Size(442, 336);
                this->Controls->Add(this->mainMenu);
                this->Icon = (cli::safe_cast < System::Drawing::Icon^  > (resources->GetObject(L"$this.Icon")));
                this->IsMdiContainer = true;
                this->MainMenuStrip = this->mainMenu;
                this->Name = L"Form1";
                this->Text = L"FWT2D";
                this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
                this->mainMenu->ResumeLayout(false);
                this->mainMenu->PerformLayout();
                this->ResumeLayout(false);
                this->PerformLayout();

        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma endregion

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
        System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                if (openPicDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                        FChildPic^ mchld = gcnew FChildPic(dir, openPicDialog->FileName);
                        mchld->MdiParent = this;
                        mchld->Show();

                }
        }


};


}

