#pragma once
#include <windows.h>
#include<stdio.h>


extern "C"



namespace DiskMonitor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	BOOL WINAPI ReadDirectoryChangesW(__in HANDLE hDirectory,
		__out_bcount_part(nBufferLength, *lpBytesReturned) LPVOID lpBuffer,
		__in DWORD nBufferLength,
		__in BOOL bWAtchSubtree,
		__in DWORD dwNotifyFilter,
		__out LPDWORD lpBytesReturned,
		__inout LPOVERLAPPED lpOverlapped,
		__in_opt LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	);
	DWORD WINAPI ThreadProc(LPVOID lpParam) {
		BOOL bRet = FALSE;
		BYTE Buffer[1024] = { 0 };
		FILE_NOTIFY_INFORMATION *pBuffer = (FILE_NOTIFY_INFORMATION *)Buffer;
		DWORD BytesReturned = 0;
		HANDLE hFile = CreateFile("c:\\", FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

		if (INVALID_HANDLE_VALUE == hFile) {
			return 1;
		}

		//	button1->Enabled = FALSE;
		//button2->Enabled = TRUE;;

		while (true)
		{
			ZeroMemory(Buffer, 0);
			bRet = ReadDirectoryChangesW(hFile, &Buffer, sizeof(Buffer), TRUE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_ATTRIBUTES | FILE_NOTIFY_CHANGE_LAST_WRITE,
				&BytesReturned, NULL, NULL);
			if (bRet == TRUE) {
				char szFileName[MAX_PATH] = { 0 };
				WideCharToMultiByte(CP_ACP, 0, pBuffer->FileName, pBuffer->FileNameLength / 2,
					szFileName, MAX_PATH, NULL, NULL);
				String^ GG = gcnew String(szFileName);
				switch (pBuffer->Action)
				{
				case FILE_ACTION_ADDED:
				{
					MessageBox::Show("G", "6666666666666");
					//textBox1->Text += "新增 : " + GG;
					//textBox1->Text += szFileName;
					break;
				}
				case FILE_ACTION_REMOVED:
				{
					//textBox1->Text += "刪除 : " + GG;
				}
				case FILE_ACTION_MODIFIED:
				{
					//textBox1->Text += "修改 : " + GG;
				}
				case FILE_ACTION_RENAMED_OLD_NAME:
				{
					//textBox1->Text += "重命名 : ";
					if (pBuffer->NextEntryOffset != 0) {
						FILE_NOTIFY_INFORMATION *tmpBuffer = (FILE_NOTIFY_INFORMATION *)
							((DWORD)pBuffer + pBuffer->NextEntryOffset);
						switch (tmpBuffer->Action)
						{
						case FILE_ACTION_RENAMED_NEW_NAME:
						{
							ZeroMemory(szFileName, MAX_PATH);
							WideCharToMultiByte(CP_ACP, 0, tmpBuffer->FileName, tmpBuffer->FileNameLength / 2, szFileName
								, MAX_PATH, NULL, NULL);
							//textBox1->Text += GG;
						}
						default:
							break;
						}
					}
				}
				case FILE_ACTION_RENAMED_NEW_NAME:
				{
					//textBox1->Text += "重命名 : " + GG;
				}
				default:
					break;
				}
			}
		}
		CloseHandle(hFile);
		return 0;
	}
	
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox1->Size = System::Drawing::Size(621, 188);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 206);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(290, 26);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(343, 206);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(290, 26);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Stop";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(645, 244);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();



		}
		
#pragma endregion

		

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		
		HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
		if (hThread == NULL) {
			MyForm::Close();
		}
		WaitForSingleObject(hThread,INFINITE);
		CloseHandle(hThread);
		MyForm::Close();
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}
