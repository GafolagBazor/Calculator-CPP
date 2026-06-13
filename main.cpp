#include "main.h"

namespace MyClrApp {

    MainAppForm::MainAppForm(void) {
        InitializeForm();
    }

    void MainAppForm::InitializeForm() {
        this->Text = L"\u041a\u0430\u043b\u044c\u043a\u0443\u043b\u044f\u0442\u043e\u0440"; // Калькулятор
        this->Size = System::Drawing::Size(500, 600);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->MaximizeBox = false;

        // === ВСТАВЛЯЕМ ЭТОТ БЛОК ДЛЯ ЗАГРУЗКИ ЗНАЧКА ===
        String^ exePath = System::IO::Path::GetDirectoryName(Application::ExecutablePath);
        String^ iconPath = System::IO::Path::Combine(exePath, "app.ico");

        if (System::IO::File::Exists(iconPath)) {
            this->Icon = gcnew System::Drawing::Icon(iconPath);
        }
        else {
            this->ShowIcon = true;
        }
        // ==============================================

        System::Drawing::Font^ mainFont = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Regular);

        // Ввод 1
        inputLabel1 = gcnew Label();
        inputLabel1->Text = L"\u0427\u0438\u0441\u043b\u043e 1:"; // Число 1:
        inputLabel1->Location = Point(30, 20);
        inputLabel1->Size = System::Drawing::Size(180, 20);
        inputLabel1->Font = mainFont;

        inputTextBox1 = gcnew TextBox();
        inputTextBox1->Location = Point(30, 45);
        inputTextBox1->Size = System::Drawing::Size(180, 27);
        inputTextBox1->Font = mainFont;
        inputTextBox1->Text = "0";
        inputTextBox1->KeyPress += gcnew KeyPressEventHandler(this, &MainAppForm::OnTextBoxKeyPress);

        // Ввод 2
        inputLabel2 = gcnew Label();
        inputLabel2->Text = L"\u0427\u0438\u0441\u043b\u043e 2:"; // Число 2:
        inputLabel2->Location = Point(260, 20);
        inputLabel2->Size = System::Drawing::Size(180, 20);
        inputLabel2->Font = mainFont;

        inputTextBox2 = gcnew TextBox();
        inputTextBox2->Location = Point(260, 45);
        inputTextBox2->Size = System::Drawing::Size(180, 27);
        inputTextBox2->Font = mainFont;
        inputTextBox2->Text = "0";
        inputTextBox2->KeyPress += gcnew KeyPressEventHandler(this, &MainAppForm::OnTextBoxKeyPress);

        // Комбобокс
        comboLabel = gcnew Label();
        comboLabel->Text = L"\u0412\u044b\u0431\u0435\u0440\u0438\u0442\u0435 \u043e\u043f\u0435\u0440\u0430\u0446\u0438\u044e:"; // Выберите операцию:
        comboLabel->Location = Point(30, 90);
        comboLabel->Size = System::Drawing::Size(400, 20);
        comboLabel->Font = mainFont;

        operationComboBox = gcnew ComboBox();
        operationComboBox->Location = Point(30, 115);
        operationComboBox->Size = System::Drawing::Size(410, 27);
        operationComboBox->DropDownStyle = ComboBoxStyle::DropDownList;
        operationComboBox->Font = mainFont;

        operationComboBox->Items->Add(L"[+] \u0421\u043b\u043e\u0436\u0435\u043d\u0438\u0435");
        operationComboBox->Items->Add(L"[-] \u0412\u044b\u0447\u0438\u0442\u0430\u043d\u0438\u0435");
        operationComboBox->Items->Add(L"[*] \u0423\u043c\u043d\u043e\u0436\u0435\u043d\u0438\u0435");
        operationComboBox->Items->Add(L"[/] \u0414\u0435\u043b\u0435\u043d\u0438\u0435");
        operationComboBox->Items->Add(L"[%] \u041e\u0441\u0442\u0430\u0442\u043e\u043a \u043e\u0442 \u0434\u0435\u043b\u0435\u043d\u0438\u044f");
        operationComboBox->Items->Add(L"[X^Y] \u0412\u043e\u0437\u0432\u0435\u0434\u0435\u043d\u0438\u0435 \u0432 \u0441\u0442\u0435\u043f\u0435\u043d\u044c");
        operationComboBox->Items->Add(L"[\u221a] \u041a\u0432\u0430\u0434\u0440\u0430\u0442\u043d\u044b\u0439 \u043a\u043e\u0440\u0435\u043d\u044c");
        operationComboBox->Items->Add(L"[X^2] \u041a\u0432\u0430\u0434\u0440\u0430\u0442 \u0447\u0438\u0441\u043b\u0430");
        operationComboBox->Items->Add(L"[X^3] \u041a\u0443\u0431 \u0447\u0438\u0441\u043b\u0430");
        operationComboBox->Items->Add(L"[sin] \u0421\u0438\u043d\u0443\u0441 (rad)");
        operationComboBox->Items->Add(L"[cos] \u041a\u043e\u0441\u0438\u043d\u0443\u0441 (rad)");
        operationComboBox->Items->Add(L"[tan] \u0422\u0430\u043d\u0433\u0435\u043d\u044c\u0441 (rad)");
        operationComboBox->Items->Add(L"[ln] \u041d\u0430\u0442\u0443\u0440\u0430\u043b\u044c\u043d\u044b\u0439 \u043b\u043e\u0433\u0430\u0440\u0438\u0444\u043c");
        operationComboBox->Items->Add(L"[|X|] \u041c\u043e\u0434\u0443\u043b\u044c \u0447\u0438\u0441\u043b\u0430");
        operationComboBox->Items->Add(L"[round] \u041e\u043a\u0440\u0443\u0433\u043b\u0435\u043d\u0438\u0435");
        operationComboBox->Items->Add(L"[!] \u0424\u0430\u043a\u0442\u043e\u0440\u0438\u0430\u043b (\u0412\u0432\u043e\u0434 1)");

        operationComboBox->SelectedIndexChanged += gcnew EventHandler(this, &MainAppForm::OnSelectedIndexChanged);
        operationComboBox->SelectedIndex = 0;

        // Стиль
        styleGroupBox = gcnew GroupBox();
        styleGroupBox->Text = L"\u0426\u0432\u0435\u0442\u043e\u0432\u043e\u0439 \u0441\u0442\u0438\u043b\u044c";
        styleGroupBox->Location = Point(30, 165);
        styleGroupBox->Size = System::Drawing::Size(410, 75);
        styleGroupBox->Font = mainFont;

        radioOption1 = gcnew RadioButton();
        radioOption1->Text = L"\u0421\u0432\u0435\u0442\u043b\u044b\u0439";
        radioOption1->Location = Point(20, 28);
        radioOption1->Checked = true;

        radioOption2 = gcnew RadioButton();
        radioOption2->Text = L"\u041c\u044f\u0442\u043d\u044b\u0439";
        radioOption2->Location = Point(180, 28);

        styleGroupBox->Controls->Add(radioOption1);
        styleGroupBox->Controls->Add(radioOption2);

        // Кнопка
        actionButton = gcnew Button();
        actionButton->Text = L"\u0412\u044b\u0447\u0438\u0441\u043b\u0438\u0442\u044c"; // Вычислить
        actionButton->Location = Point(30, 260);
        actionButton->Size = System::Drawing::Size(410, 45);
        actionButton->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, FontStyle::Bold);
        actionButton->Cursor = Cursors::Hand;
        actionButton->Click += gcnew EventHandler(this, &MainAppForm::OnActionButtonClick);

        // Окно вывода RichTextBox
        resultRichTextBox = gcnew RichTextBox();
        resultRichTextBox->Location = Point(30, 325);
        resultRichTextBox->Size = System::Drawing::Size(410, 210);
        resultRichTextBox->Font = gcnew System::Drawing::Font(L"Consolas", 10, FontStyle::Bold);
        resultRichTextBox->ReadOnly = true;
        resultRichTextBox->BackColor = Color::LightGray;

        calculationWorker = gcnew BackgroundWorker();
        calculationWorker->DoWork += gcnew DoWorkEventHandler(this, &MainAppForm::DoCalculationWork);
        calculationWorker->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler(this, &MainAppForm::CalculationWorkCompleted);

        this->Controls->Add(inputLabel1);
        this->Controls->Add(inputTextBox1);
        this->Controls->Add(inputLabel2);
        this->Controls->Add(inputTextBox2);
        this->Controls->Add(comboLabel);
        this->Controls->Add(operationComboBox);
        this->Controls->Add(styleGroupBox);
        this->Controls->Add(actionButton);
        this->Controls->Add(resultRichTextBox);
    }

    void MainAppForm::OnTextBoxKeyPress(Object^ sender, KeyPressEventArgs^ e) {
        if (!Char::IsDigit(e->KeyChar) && e->KeyChar != (char)Keys::Back && e->KeyChar != '-') {
            e->Handled = true;
        }
    }

    void MainAppForm::OnSelectedIndexChanged(Object^ sender, EventArgs^ e) {
        int mode = operationComboBox->SelectedIndex;
        bool needsSecondInput = (mode <= 5);
        inputLabel2->Visible = needsSecondInput;
        inputTextBox2->Visible = needsSecondInput;
    }

    void MainAppForm::OnActionButtonClick(Object^ sender, EventArgs^ e) {
        if (radioOption2->Checked) {
            this->BackColor = Color::FromArgb(220, 245, 230);
        }
        else {
            this->BackColor = SystemColors::Control;
        }

        strNum1 = inputTextBox1->Text;
        strNum2 = inputTextBox2->Text;
        currentMode = operationComboBox->SelectedIndex;

        actionButton->Enabled = false;
        resultRichTextBox->Text = L"\u0412\u044b\u0447\u0438\u0441\u043b\u0435\u043d\u0438\u044f \u0432 \u0444\u043e\u043d\u043e\u0432\u043e\u043c \u043f\u043e\u0442\u043e\u043a\u0435 .NET...";

        calculationWorker->RunWorkerAsync();
    }

    // ПОЛНОСТЬЮ ИСПРАВЛЕННЫЙ ТЯЖЕЛЫЙ РАСЧЕТ (БЕЗ ИСПОЛЬЗОВАНИЯ STD)
    void MainAppForm::DoCalculationWork(Object^ sender, DoWorkEventArgs^ e) {
        BigInteger num1, num2;

        if (!BigInteger::TryParse(strNum1, num1)) {
            e->Result = L"\u041e\u0448\u0438\u0431\u043a\u0430: \u043d\u0435\u043a\u043e\u0440\u0440\u0435\u043a\u0442\u043d\u043e\u0435 \u0427\u0438\u0441\u043b\u043e 1!";
            return;
        }

        if (currentMode <= 5) {
            if (!BigInteger::TryParse(strNum2, num2)) {
                e->Result = L"\u041e\u0448\u0438\u0431\u043a\u0430: \u043d\u0435\u043a\u043e\u0440\u0440\u0435\u043a\u0442\u043d\u043e\u0435 \u0427\u0438\u0441\u043b\u043e 2!";
                return;
            }
            if ((currentMode == 3 || currentMode == 4) && num2 == BigInteger::Zero) {
                e->Result = L"\u041a\u0440\u0438\u0442\u0438\u0447\u0435\u0441\u043a\u0430\u044f \u043e\u0448\u0438\u0431\u043a\u0430: \u0414\u0435\u043b\u0435\u043d\u0438\u0435 \u043d\u0430 \u043d\u043e\u043b\u044c!";
                return;
            }
        }

        BigInteger result = BigInteger::Zero;
        double dNum1 = (double)num1;

        switch (currentMode) {
        case 0:
            result = num1 + num2;
            e->Result = result.ToString();
            break;
        case 1:
            result = num1 - num2;
            e->Result = result.ToString();
            break;
        case 2:
            result = num1 * num2;
            e->Result = result.ToString();
            break;
        case 3:
            result = num1 / num2;
            e->Result = result.ToString();
            break;
        case 4:
            result = num1 % num2;
            e->Result = result.ToString();
            break;
        case 5: {
            // Безопасное приведение BigInteger к int с перехватом переполнения
            int power;
            try {
                power = (int)num2;
            }
            catch (OverflowException^) {
                e->Result = L"\u041e\u0448\u0438\u0431\u043a\u0430: \u0441\u0442\u0435\u043f\u0435\u043d\u044c \u0441\u043b\u0438\u0448\u043a\u043e\u043c \u0431\u043e\u043b\u044c\u0448\u0430\u044f!";
                return;
            }

            if (power < 0) {
                e->Result = L"\u0421\u0442\u0435\u043f\u0435\u043d\u044c \u043d\u0435 \u043c\u043e\u0436\u0435\u0442 \u0431\u044b\u0442\u044c \u043c\u0435\u043d\u044c\u0448\u0435 0!";
                return;
            }
            if (power > 3000) {
                e->Result = L"\u041e\u0433\u0440\u0430\u043d\u0438\u0447\u0435\u043d\u0438\u0435 \u0441\u0442\u0435\u043f\u0435\u043d\u0438 \u0434\u043e 3000 \u0440\u0430\u0434\u0438 \u041e\u0417\u0423.";
                return;
            }
            result = BigInteger::Pow(num1, power);
            e->Result = result.ToString();
            break;
        }
        case 6: {
            if (num1 < BigInteger::Zero) {
                e->Result = L"\u041e\u0448\u0438\u0431\u043a\u0430: \u043a\u043e\u0440\u0435\u043d\u044c \u0438\u0437 \u043e\u0442\u0440\u0438\u0446\u0430\u0442\u0435\u043b\u044c\u043d\u043e\u0433\u043e \u0447\u0438\u0441\u043b\u0430!";
                return;
            }
            e->Result = Convert::ToString(Math::Sqrt(dNum1));
            break;
        }
        case 7:
            e->Result = (num1 * num1).ToString();
            break;
        case 8:
            result = num1 * num1 * num1;
            e->Result = result.ToString();
            break;
        case 9:
            e->Result = Convert::ToString(Math::Sin(dNum1));
            break;
        case 10:
            e->Result = Convert::ToString(Math::Cos(dNum1));
            break;
        case 11:
            e->Result = Convert::ToString(Math::Tan(dNum1));
            break;
        case 12: {
            if (num1 <= BigInteger::Zero) {
                e->Result = L"\u041e\u0448\u0438\u0431\u043a\u0430: \u043b\u043e\u0433\u0430\u0440\u0438\u0444\u043c \u0434\u043e\u043b\u0436\u0435\u043d \u0431\u044b\u0442\u044c > 0!";
                return;
            }
            e->Result = Convert::ToString(Math::Log(dNum1));
            break;
        }
        case 13:
            e->Result = BigInteger::Abs(num1).ToString();
            break;
        case 14:
            e->Result = num1.ToString();
            break;
        case 15: {
            // Безопасное приведение BigInteger к int с перехватом переполнения
            int limit;
            try {
                limit = (int)num1;
            }
            catch (OverflowException^) {
                e->Result = L"\u041e\u0448\u0438\u0431\u043a\u0430: \u0447\u0438\u0441\u043b\u043e \u0441\u043b\u0438\u0448\u043a\u043e\u043c \u0431\u043e\u043b\u044c\u0448\u043e\u0435 \u0434\u043b\u044f \u0444\u0430\u043a\u0442\u043e\u0440\u0438\u0430\u043b\u0430!";
                return;
            }

            if (limit < 0) {
                e->Result = L"\u0424\u0430\u043a\u0442\u043e\u0440\u0438\u0430\u043b \u043e\u043f\u0440\u0435\u0434\u0435\u043b\u0435\u043d \u0442\u043e\u043b\u044c\u043a\u043e \u0434\u043b\u044f >= 0!";
                return;
            }
            if (limit > 2000) {
                e->Result = L"\u041e\u0433\u0440\u0430\u043d\u0438\u0447\u0435\u043d\u0438\u0435 \u0441\u0442\u0435\u043f\u0435\u043d\u0438 \u0444\u0430\u043a\u0442\u043e\u0440\u0438\u0430\u043b\u0430 \u0434\u043e 2000.";
                return;
            }
            BigInteger fact = 1;
            for (int i = 2; i <= limit; i++) {
                fact *= i;
            }
            e->Result = fact.ToString();
            break;
        }
        default:
            e->Result = "0";
            break;
        }
    }

    void MainAppForm::CalculationWorkCompleted(Object^ sender, RunWorkerCompletedEventArgs^ e) {
        String^ finalResult = dynamic_cast<String^>(e->Result);
        resultRichTextBox->Text = L"\u0412\u044b\u0447\u0438\u0441\u043b\u0435\u043d\u0438\u0435...\n" + "\u041e\u0442\u0432\u0435\u0442: " + finalResult; /*Вычисление... 
        Ответ: */
        actionButton->Enabled = true;
    }
}

// Главная точка входа приложения .NET
[STAThreadAttribute]
int main(array<System::String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MyClrApp::MainAppForm());
    return 0;
}

