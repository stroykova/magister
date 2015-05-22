#pragma once

#include <fstream>
#include <string>

#include "../opencv_proj/WaveletPack.h"

namespace visual_proj {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(11, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(89, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"�������� ����:";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 25);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(239, 20);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(257, 23);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(28, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(11, 57);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(135, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"����������� ������, %:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(12, 83);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 4;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 119);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(134, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"����������";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(152, 119);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(133, 23);
			this->button3->TabIndex = 6;
			this->button3->Text = L"������������";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(152, 57);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(133, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"����������� ������, %:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(152, 83);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 13);
			this->label4->TabIndex = 8;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(308, 162);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"Form1";
			this->Text = L"�������-��������������";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
					{
						textBox1->Text = openFileDialog1->FileName;

					}
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

			 String ^fileName = textBox1->Text;
			 if (!System::IO::File::Exists(fileName))
			 {
				MessageBox::Show("��������� ��� �����");
				return;
			 }

			 String ^perc = textBox2->Text;
			 __int32 i;
			 if (!System::Int32::TryParse(perc, i) || i <= 0 || i >= 100)
			 {
				MessageBox::Show("��������� ������� ����������� ������");
				return;
			 }

			char* filename = (char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName).ToPointer();
			float result = compress(filename, i);
			label4->Text = result.ToString();
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

			 String ^fileName = textBox1->Text;
			 if (!System::IO::File::Exists(fileName))
			 {
				MessageBox::Show("��������� ��� �����");
				return;
			 }
			 char* filename = (char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName).ToPointer();
			 decode(filename);
		 }
};
}

