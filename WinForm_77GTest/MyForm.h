#pragma once
#include<vector>
#include"RadarDef.h"
typedef unsigned int uint;
typedef Radar_77G Radar;
namespace WinForm_77GTest {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::IO::Ports;
	using namespace System::Runtime::InteropServices;
	using namespace System::Windows::Forms::DataVisualization::Charting;
	using namespace std;
	vector<Radar> validRadar;
	uint falsecounter[2] = { 0 };
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
			ComPortRefresh();
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
	private: System::IO::Ports::SerialPort^  serialPort_Radar77;
	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
	private:cli::array<Byte>^ SerialBuffer = gcnew cli::array<Byte>(10000);
			uint CarSpeed = 0;
	private: System::Windows::Forms::Button^  Btn_Start;
	private: System::Windows::Forms::ComboBox^  cBox_Radar;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;

			 double YawRate = 0;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
			 /// 這個方法的內容。
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
				 System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
				 System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
				 this->serialPort_Radar77 = (gcnew System::IO::Ports::SerialPort(this->components));
				 this->Btn_Start = (gcnew System::Windows::Forms::Button());
				 this->cBox_Radar = (gcnew System::Windows::Forms::ComboBox());
				 this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // serialPort_Radar77
				 // 
				 this->serialPort_Radar77->BaudRate = 230400;
				 this->serialPort_Radar77->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &MyForm::serialPort_Radar77_DataReceived);
				 // 
				 // Btn_Start
				 // 
				 this->Btn_Start->Location = System::Drawing::Point(986, 24);
				 this->Btn_Start->Name = L"Btn_Start";
				 this->Btn_Start->Size = System::Drawing::Size(75, 23);
				 this->Btn_Start->TabIndex = 0;
				 this->Btn_Start->Text = L"Start";
				 this->Btn_Start->UseVisualStyleBackColor = true;
				 this->Btn_Start->Click += gcnew System::EventHandler(this, &MyForm::Btn_Start_Click);
				 // 
				 // cBox_Radar
				 // 
				 this->cBox_Radar->FormattingEnabled = true;
				 this->cBox_Radar->Location = System::Drawing::Point(957, 90);
				 this->cBox_Radar->Name = L"cBox_Radar";
				 this->cBox_Radar->Size = System::Drawing::Size(121, 20);
				 this->cBox_Radar->TabIndex = 1;
				 // 
				 // chart1
				 // 
				 chartArea1->Name = L"ChartArea1";
				 this->chart1->ChartAreas->Add(chartArea1);
				 legend1->Name = L"Legend1";
				 this->chart1->Legends->Add(legend1);
				 this->chart1->Location = System::Drawing::Point(13, 13);
				 this->chart1->Name = L"chart1";
				 series1->ChartArea = L"ChartArea1";
				 series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
				 series1->Legend = L"Legend1";
				 series1->Name = L"Series1";
				 this->chart1->Series->Add(series1);
				 this->chart1->Size = System::Drawing::Size(909, 538);
				 this->chart1->TabIndex = 2;
				 this->chart1->Text = L"chart1";
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(1122, 572);
				 this->Controls->Add(this->chart1);
				 this->Controls->Add(this->cBox_Radar);
				 this->Controls->Add(this->Btn_Start);
				 this->Name = L"MyForm";
				 this->Text = L"MyForm";
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
				 this->ResumeLayout(false);

			 }
#pragma endregion
	private: System::Void serialPort_Radar77_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
		//cli::array<Byte>^ SerialBuffer = gcnew cli::array<Byte>(1024);
		System::String ^SpeedCommand = "SpdGyroData" + " " + CarSpeed.ToString() + " " + Math::Round(YawRate, 2).ToString();
		serialPort_Radar77->WriteLine(SpeedCommand);
		uint readBufferLength = serialPort_Radar77->Read(SerialBuffer, 0, SerialBuffer->Length);
		if (readBufferLength >= SerialBuffer->Length)
			serialPort_Radar77->DiscardInBuffer();
		for (uint i = 0; i < readBufferLength; i++)
		{

			if (SerialBuffer[i] == 0x52 && SerialBuffer[i+514] == 0x54)
			{
				validRadar.resize(0);
				Byte checksum = 0x52;
			    pin_ptr<System::Byte> p = &SerialBuffer[i+1];
				unsigned char* ReadBufferIndex = p;
				Radar temp;
				for (uint8 j = 0; j < 32; j++)
				{
				 memcpy(&temp, ReadBufferIndex, sizeof(temp));
				 ReadBufferIndex += sizeof(Radar);
				 if (temp.getTargetPriority() != 0)
					 validRadar.push_back(temp);
				 checksum += temp.getSum();
				}
				
			}

		}
		if ((falsecounter[0] + falsecounter[1]) >= 10000)
			int a = 99;

	}
	private: System::Void Btn_Start_Click(System::Object^  sender, System::EventArgs^  e) {
		serialPort_Radar77->PortName = cBox_Radar->Text;
		serialPort_Radar77->BaudRate = 230400;
		serialPort_Radar77->StopBits = StopBits::One;
		serialPort_Radar77->Parity = Parity::None;
		serialPort_Radar77->DataBits = 8;
		serialPort_Radar77->Open();
		System::String ^SpeedCommand = "SpdGyroData" + " " + CarSpeed.ToString() + " " + Math::Round(YawRate, 2).ToString()+".00";
		serialPort_Radar77->WriteLine(SpeedCommand);
	}
	private:void ComPortRefresh(void)
	{
		cBox_Radar->Items->Clear();
		cli::array<System::String^>^ Port = SerialPort::GetPortNames();
		cBox_Radar->Items->AddRange(Port);
		
	}
	private:delegate void SetChartDelegate(Chart^_chart, Series^ _series);

	};
}
