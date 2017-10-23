#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;


#include "lib\basefwt.h"
#include "lib\fwt2d.h"

#include "dlgfltselect.h"

namespace Img
{

/// <summary>
/// Summary for FChildPic
///
/// WARNING: If you change the name of this class, you will need to change the
///          'Resource File Name' property for the managed resource compiler tool
///          associated with all .resx files this class depends on.  Otherwise,
///          the designers will not be able to interact properly with localized
///          resources associated with this form.
/// </summary>
public ref class FChildPic : public System::Windows::Forms::Form
{

        bool status;       //false if error on loading image

        String^ m_dir;    //current dir

        String^ m_caption; //form caption

        String^ m_fname;  //picture name
        Bitmap^ m_image;  //loaded image
        Bitmap^ m_clone;  //copy of image
        Graphics^ g;      //graphics from m_clone
        Pen^ bpen;        //black pen

        unsigned char *mr, *mg, *mb;  //r,g,b
        int width;        //r,g,b width for FWT2D
        int height;       //r,g,b heigth for FWT2D

        wchar_t* m_filter;            //fwt filter
        FWT2D *rfwt, *gfwt, *bfwt;    //fwt transforms class
        int J;                       //number of FWT2D scales
        int TH;                      //threshold




private:
        System::Windows::Forms::MenuStrip^  childMenu;
private:
        System::Windows::Forms::ToolStripMenuItem^  transToolStripMenuItem;
private:
        System::Windows::Forms::ToolStripMenuItem^  transrgbToolStripMenuItem;
private:
        System::Windows::Forms::PictureBox^  pictureBox;
private: System::Windows::Forms::ToolStripMenuItem^  denoiseToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
private: System::Windows::Forms::ToolStripMenuItem^  absValuesToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  contrastStretchToolStripMenuItem;



private:
        System::Windows::Forms::ToolStripMenuItem^  synthrgbToolStripMenuItem;




public:
        FChildPic(void) : status(false), rfwt(0), gfwt(0), bfwt(0), J(0), mr(0), mg(0), mb(0), m_filter(0) {
                InitializeComponent();
        }
        FChildPic(String^ dir, String^ fname) : m_dir(dir), m_fname(fname), //picture file name
                        status(false), rfwt(0), gfwt(0), bfwt(0), J(3), mr(0), mg(0), mb(0),
                        m_filter(0), TH(0)

        {
                InitializeComponent();

                try {
                        m_image = gcnew Bitmap(fname);
                        m_clone = m_image->Clone(Drawing::Rectangle(0, 0, m_image->Width, m_image->Height), m_image->PixelFormat);
                        g = Graphics::FromImage(m_clone);

                        bpen = gcnew Pen(Color::FromArgb(0, 0, 0));

                        m_filter = new wchar_t[_MAX_PATH];
                        wcscpy(m_filter, L"empty");

                        status = true;
                } catch (ArgumentException^ a) {
                        MessageBox::Show(a->Message, a->Source, MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
        }


protected:
        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        ~FChildPic() {
                if (components) {
                        delete components;
                }

                closeRGB();
                closeFWT();
                if (m_filter) delete[] m_filter;
                //g->Dispose();
        }

protected:

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
                System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FChildPic::typeid));
                this->childMenu = (gcnew System::Windows::Forms::MenuStrip());
                this->transToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->transrgbToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->synthrgbToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
                this->denoiseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->absValuesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->contrastStretchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
                this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
                this->childMenu->SuspendLayout();
                (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
                this->SuspendLayout();
                // 
                // childMenu
                // 
                this->childMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->transToolStripMenuItem});
                this->childMenu->Location = System::Drawing::Point(0, 0);
                this->childMenu->Name = L"childMenu";
                this->childMenu->Size = System::Drawing::Size(342, 24);
                this->childMenu->TabIndex = 1;
                this->childMenu->Visible = false;
                // 
                // transToolStripMenuItem
                // 
                this->transToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->transrgbToolStripMenuItem, 
                        this->synthrgbToolStripMenuItem, this->toolStripMenuItem1, this->denoiseToolStripMenuItem, this->absValuesToolStripMenuItem, 
                        this->contrastStretchToolStripMenuItem});
                this->transToolStripMenuItem->Name = L"transToolStripMenuItem";
                this->transToolStripMenuItem->Size = System::Drawing::Size(79, 20);
                this->transToolStripMenuItem->Text = L"Transforms";
                // 
                // transrgbToolStripMenuItem
                // 
                this->transrgbToolStripMenuItem->Name = L"transrgbToolStripMenuItem";
                this->transrgbToolStripMenuItem->Size = System::Drawing::Size(192, 22);
                this->transrgbToolStripMenuItem->Text = L"FWT2D RGB transform";
                this->transrgbToolStripMenuItem->Click += gcnew System::EventHandler(this, &FChildPic::transrgbToolStripMenuItem_Click);
                // 
                // synthrgbToolStripMenuItem
                // 
                this->synthrgbToolStripMenuItem->Name = L"synthrgbToolStripMenuItem";
                this->synthrgbToolStripMenuItem->Size = System::Drawing::Size(192, 22);
                this->synthrgbToolStripMenuItem->Text = L"FWT2D RGB synth";
                this->synthrgbToolStripMenuItem->Click += gcnew System::EventHandler(this, &FChildPic::synthrgbToolStripMenuItem_Click);
                // 
                // toolStripMenuItem1
                // 
                this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
                this->toolStripMenuItem1->Size = System::Drawing::Size(189, 6);
                // 
                // denoiseToolStripMenuItem
                // 
                this->denoiseToolStripMenuItem->Name = L"denoiseToolStripMenuItem";
                this->denoiseToolStripMenuItem->Size = System::Drawing::Size(192, 22);
                this->denoiseToolStripMenuItem->Text = L"Denoise";
                this->denoiseToolStripMenuItem->Click += gcnew System::EventHandler(this, &FChildPic::denoiseToolStripMenuItem_Click);
                // 
                // absValuesToolStripMenuItem
                // 
                this->absValuesToolStripMenuItem->Name = L"absValuesToolStripMenuItem";
                this->absValuesToolStripMenuItem->Size = System::Drawing::Size(192, 22);
                this->absValuesToolStripMenuItem->Text = L"Abs values";
                this->absValuesToolStripMenuItem->Click += gcnew System::EventHandler(this, &FChildPic::absValuesToolStripMenuItem_Click);
                // 
                // contrastStretchToolStripMenuItem
                // 
                this->contrastStretchToolStripMenuItem->Name = L"contrastStretchToolStripMenuItem";
                this->contrastStretchToolStripMenuItem->Size = System::Drawing::Size(192, 22);
                this->contrastStretchToolStripMenuItem->Text = L"Contrast stretch";
                this->contrastStretchToolStripMenuItem->Click += gcnew System::EventHandler(this, &FChildPic::contrastStretchToolStripMenuItem_Click);
                // 
                // pictureBox
                // 
                this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
                this->pictureBox->Location = System::Drawing::Point(0, 24);
                this->pictureBox->Name = L"pictureBox";
                this->pictureBox->Size = System::Drawing::Size(342, 216);
                this->pictureBox->TabIndex = 0;
                this->pictureBox->TabStop = false;
                // 
                // FChildPic
                // 
                this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
                this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
                this->BackColor = System::Drawing::SystemColors::ControlLight;
                this->ClientSize = System::Drawing::Size(342, 240);
                this->Controls->Add(this->pictureBox);
                this->Controls->Add(this->childMenu);
                this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
                this->MainMenuStrip = this->childMenu;
                this->Name = L"FChildPic";
                this->Text = L"FChildPic";
                this->Resize += gcnew System::EventHandler(this, &FChildPic::FChildPic_Resize);
                this->Shown += gcnew System::EventHandler(this, &FChildPic::FChildPic_Shown);
                this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FChildPic::FChildPic_FormClosing);
                this->Load += gcnew System::EventHandler(this, &FChildPic::FChildPic_Load);
                this->childMenu->ResumeLayout(false);
                this->childMenu->PerformLayout();
                (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
                this->ResumeLayout(false);
                this->PerformLayout();

        }
#pragma endregion
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /*
           m_image    //picture
           m_clone    //copy of picture

           picBox->Image = m_clone

           Graphics^ g = Graphics::FromImage(m_clone);   //from m_clone image


            //drawing
             g->draw()
             picBox->Invalidate()

           //rubberbanding
             g->draw(m_img)
             g->draw()
             picBox->Invalidate()
        */



        /////////////////////////////get/set r,g,b components from image//////////////////////////////////////////////////////////////////
private:
        void initRGB(Bitmap^ img, int scale) {
                closeRGB();

                J = scale;
                scale = (int)pow(2.0f, (float)scale);

                width = (img->Width % scale) ? img->Width - (img->Width % scale) : img->Width;
                height = (img->Height % scale) ? img->Height - (img->Height % scale) : img->Height;

                mr = (unsigned char *)malloc(width * height * sizeof(unsigned char));
                mg = (unsigned char *)malloc(width * height * sizeof(unsigned char));
                mb = (unsigned char *)malloc(width * height * sizeof(unsigned char));
        }
private:
        void closeRGB() {
                if (mr) {
                        free(mr);
                        mr = 0;
                }
                if (mg) {
                        free(mg);
                        mg = 0;
                }
                if (mb) {
                        free(mb);
                        mb = 0;
                }
        }

private:
        bool getRGB(unsigned char *r, unsigned char *g, unsigned char *b, Bitmap^ img) {
                BitmapData^ pbits = img->LockBits(Drawing::Rectangle(0, 0, width, height), ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
                if (pbits) {
                        //IntPtr ptr(pbits->Scan0);
                        unsigned char *pdata = (unsigned char *)((IntPtr)(pbits->Scan0)).ToPointer();

                        for (int y = 0; y < height; y++) {
                                for (int x = 0; x < width; x++) {
                                        *b++ = pdata[3*x+0];
                                        *g++ = pdata[3*x+1];
                                        *r++ = pdata[3*x+2];
                                }
                                pdata += pbits->Stride;
                        }

                        img->UnlockBits(pbits);
                } else {
                        MessageBox::Show("Failed LockBits.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return false;
                }

                return true;
        }

private:
        bool setRGB(Bitmap^ img, unsigned char *r, unsigned char *g, unsigned char *b) {
                BitmapData^ pbits = img->LockBits(Drawing::Rectangle(0, 0, width, height), ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
                if (pbits) {
                        //IntPtr ptr(pbits->Scan0);
                        unsigned char *pdata = (unsigned char *)((IntPtr)(pbits->Scan0)).ToPointer();

                        for (int y = 0; y < height; y++) {
                                for (int x = 0; x < width; x++) {
                                        pdata[3*x+0] = *b++;
                                        pdata[3*x+1] = *g++;
                                        pdata[3*x+2] = *r++;
                                }
                                pdata += pbits->Stride;
                        }

                        img->UnlockBits(pbits);
                } else {
                        MessageBox::Show("Failed LockBits.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return false;
                }

                return true;
        }
private:
        bool setRGB(Bitmap^ img, char *r, char *g, char *b) {
                BitmapData^ pbits = img->LockBits(Drawing::Rectangle(0, 0, width, height), ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
                if (pbits) {
                        //IntPtr ptr(pbits->Scan0);
                        unsigned char *pdata = (unsigned char *)((IntPtr)(pbits->Scan0)).ToPointer();

                        for (int y = 0; y < height; y++) {
                                for (int x = 0; x < width; x++) {
                                        pdata[3*x+0] = (unsigned char)(int(*b++) + 128);
                                        pdata[3*x+1] = (unsigned char)(int(*g++) + 128);
                                        pdata[3*x+2] = (unsigned char)(int(*r++) + 128);
                                }
                                pdata += pbits->Stride;
                        }

                        img->UnlockBits(pbits);
                } else {
                        MessageBox::Show("Failed LockBits.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return false;
                }

                return true;
        }

private:
        bool initFWT(wchar_t *filter) {
                closeFWT();

                rfwt = new FWT2D(filter);
                gfwt = new FWT2D(filter);
                bfwt = new FWT2D(filter);

                int status = 0;
                if (rfwt->status(status) || gfwt->status(status) || bfwt->status(status))
                        return false;

                rfwt->init(width, height);
                gfwt->init(width, height);
                bfwt->init(width, height);

                return true;
        }
private:
        void closeFWT() {
                if (rfwt) {
                        delete rfwt;
                        rfwt = 0;
                }
                if (gfwt) {
                        delete gfwt;
                        gfwt = 0;
                }
                if (bfwt) {
                        delete bfwt;
                        bfwt = 0;
                }
        }
private:
        float PSNR(Bitmap^ img1, Bitmap^ img2) {
                BitmapData^ pbits1 = img1->LockBits(Drawing::Rectangle(0, 0, width, height), ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
                BitmapData^ pbits2 = img2->LockBits(Drawing::Rectangle(0, 0, width, height), ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
                if (pbits1 && pbits2) {
                        //IntPtr ptr(pbits->Scan0);
                        unsigned char *pdata1 = (unsigned char *)((IntPtr)(pbits1->Scan0)).ToPointer();
                        unsigned char *pdata2 = (unsigned char *)((IntPtr)(pbits2->Scan0)).ToPointer();

                        float res = 0.0f;

                        for (int y = 0; y < height; y++) {
                                for (int x = 0; x < width; x++) {
                                        res += pow((float)pdata1[3*x+0] - (float)pdata2[3*x+0] , 2.0f);
                                        res += pow((float)pdata1[3*x+1] - (float)pdata2[3*x+1] , 2.0f);
                                        res += pow((float)pdata1[3*x+2] - (float)pdata2[3*x+2] , 2.0f);
                                }
                                pdata1 += pbits1->Stride;
                                pdata2 += pbits2->Stride;
                        }

                        img1->UnlockBits(pbits1);
                        img2->UnlockBits(pbits2);

                        if (res == 0.0f) res = 0.0000000000001f;

                        return 10.0f * log10(255.0f*255.0f*3.0f*float(width*height) / res);

                } else {
                        MessageBox::Show("Failed LockBits.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        if (pbits1)img1->UnlockBits(pbits1);
                        if (pbits2)img2->UnlockBits(pbits2);
                        return 0.0f;
                }

                return true;

        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






        ///////////////////////////form loading///////////////////////////////////////////////////////////////////////////////////////
private:
        System::Void FChildPic_Load(System::Object^  sender, System::EventArgs^  e) {
                if (!status) return;

                m_caption = Path::GetFileName(m_fname);
                Text = m_caption;
                BackColor = Color::FromArgb(255, 255, 255);

                pictureBox->Image = m_clone;

                if (MdiParent->ClientSize.Width > m_image->Width && MdiParent->ClientSize.Height > m_image->Height) {
                        Width = m_image->Width + (Width - ClientSize.Width);
                        Height = m_image->Height + (Height - ClientSize.Height);
                } else {
                        AutoScroll = true;
                        AutoScrollMinSize = m_image->Size;
                }

        }
private:
        System::Void FChildPic_Shown(System::Object^  sender, System::EventArgs^  e) {
                if (!status)
                        Close();
        }

private:
        System::Void FChildPic_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
                //m_image->Dispose();
        }
private:
        System::Void FChildPic_Resize(System::Object^  sender, System::EventArgs ^  e) {
                if (!status) return;

                if (ClientSize.Width > m_image->Width && ClientSize.Height > m_image->Height) {
                        AutoScroll = false;
                        AutoScrollMinSize.Width = 0;
                        AutoScrollMinSize.Height = 0;
                        pictureBox->SizeMode = PictureBoxSizeMode::CenterImage;
                        // addx = ClientSize.Width - m_img->Width;
                        // addy = ClientSize.Height - m_img->Height;
                } else {
                        AutoScroll = true;
                        AutoScrollMinSize = m_image->Size;
                        pictureBox->SizeMode = PictureBoxSizeMode::Normal;
                        // addx=addy=0;
                }

        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






        //////////////////RGB transforms/////////////////////////////////////////////////////////////////////////////////////////
private:
        System::Void transrgbToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                wchar_t filter[_MAX_PATH];
                int scales;

                //Do dialog and get filter,J,TH/////////////////////////////////////////
                DlgFltSelect^ dlg = gcnew DlgFltSelect(m_dir + "\\filters");
                dlg->m_scales = J;
                dlg->m_th = TH;
                if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                        wcscpy(filter, dlg->m_filter);
                        scales = dlg->m_scales;
                        TH = dlg->m_th;
                } else {
                        //dlg->Dispose(true);
                        return;
                }
                ////////////////////////////////////////////////////////////////////////



                //if different scale or filter
                if (J != scales || wcscmp(filter, m_filter) != 0) {
                        //1. init r,g,b
                        initRGB(m_clone, scales);    //set width,height deallocate/allocate r,g,b
                        //2. init fwts
                        if (!initFWT(filter)) {
                                MessageBox::Show(gcnew String(filter), "Filter error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                                return;
                        }
                }

                //g->DrawImage(m_image,0,0);              //copy m_image to m_clone
                getRGB(mr, mg, mb, m_image);            //copy image data to r,g,b components

                //perform FWT
                rfwt->trans(mr, scales, TH);
                gfwt->trans(mg, scales, TH);
                bfwt->trans(mb, scales, TH);

                setRGB(m_clone, rfwt->getspec(), gfwt->getspec(), bfwt->getspec()); //copy specs to clone image


                //calculate nonzeros////////////////////////////////////
                int nz = 0;
                char *pspec = rfwt->getspec();
                for (int i = 0; i < width*height; i++)
                        if (pspec[i] == 0) nz++;
                pspec = gfwt->getspec();
                for (int i = 0; i < width*height; i++)
                        if (pspec[i] == 0) nz++;
                pspec = bfwt->getspec();
                for (int i = 0; i < width*height; i++)
                        if (pspec[i] == 0) nz++;

                nz = 3 * width * height - nz;
                m_caption = Path::GetFileName(m_fname) + " " + dlg->fltname + " " + String::Format("{0}/{1}", J, TH) + "  " + String::Format(" nonzeros: {0}", ((float)nz * 100.0f) / float(3 * width * height));
                Text = m_caption;



                //draw FWT levels///////////////////////////////////////
                int W = width;
                int H = height;
                for (int j = 0; j < J; j++) {
                        g->DrawRectangle(bpen, 0, H / 2, W / 2, H / 2);
                        g->DrawRectangle(bpen, W / 2, 0, W / 2, H / 2);
                        g->DrawRectangle(bpen, W / 2, H / 2, W / 2, H / 2);

                        W /= 2;
                        H /= 2;
                }
                //draw FWT levels///////////////////////////////////////


                pictureBox->Invalidate();
        }
private:
        System::Void synthrgbToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                if (rfwt && gfwt && bfwt) {
                        rfwt->synth(mr);
                        gfwt->synth(mg);
                        bfwt->synth(mb);

                        setRGB(m_clone, mr, mg, mb);

                        //compute distortion with original
                        Text = m_caption + "   " + String::Format("{0}dB", PSNR(m_image, m_clone));

                        pictureBox->Invalidate();
                }
        }
        //////////////////RGB transforms/////////////////////////////////////////////////////////////////////////////////////////

private: 
        System::Void denoiseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                if (rfwt && gfwt && bfwt) {

                        rfwt->remove_LLband();
                        gfwt->remove_LLband();
                        bfwt->remove_LLband();                        

                        setRGB(m_clone, rfwt->getspec(), gfwt->getspec(), bfwt->getspec()); //copy specs to clone image

                        //draw FWT levels///////////////////////////////////////
                        int W = width;
                        int H = height;
                        for (int j = 0; j < J; j++) {
                                g->DrawRectangle(bpen, 0, H / 2, W / 2, H / 2);
                                g->DrawRectangle(bpen, W / 2, 0, W / 2, H / 2);
                                g->DrawRectangle(bpen, W / 2, H / 2, W / 2, H / 2);

                                W /= 2;
                                H /= 2;
                        }
                        //draw FWT levels///////////////////////////////////////

                        pictureBox->Invalidate();
                }
        }

private: 
        System::Void absValuesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                if (mr && mg && mb) {
                        for (int i = 0; i < width * height; i++) {
                                mr[i] = abs((int)mr[i] - 128);
                                mg[i] = abs((int)mg[i] - 128);
                                mb[i] = abs((int)mb[i] - 128);
                        }
                        setRGB(m_clone, mr, mg, mb);
                        pictureBox->Invalidate();
                }
        }
private: 
        void normalize(unsigned char* data, unsigned int size, float a, float b) {
                float min = (float)data[0];
                float max = (float)data[0];
                for (unsigned int i = 0; i < size; i++) {
                        if ((float)data[i] < min)
                                min = data[i];
                        if ((float)data[i] > max)
                                max = data[i];
                }

                for (unsigned int i = 0; i < size; i++) {
                        float val = (float)data[i] * 7.0f;//((float)data[i] - min) * ((b - a) / (max - min)) + a;
                        if (val < 0.0f)
                                val = 0.0f;
                        if (val > 255.0f)
                                val = 255.0f;
                        data[i] = (unsigned char)val;
                }
        }
        System::Void contrastStretchToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
                if (mr && mg && mb) {
                
                        normalize(mr, width * height, 0.0f, 255.0f);
                        normalize(mg, width * height, 0.0f, 255.0f);
                        normalize(mb, width * height, 0.0f, 255.0f);

                        setRGB(m_clone, mr, mg, mb);
                        pictureBox->Invalidate();
                }
        }
};

}
