#include <iostream>
#include <list>
#include <string>
#include <regex>

struct Payment {
	std::string sName;
	std::string sDirection;
	float fValue;
};

std::list<struct Payment> oPayments;
std::list<struct Payment>::iterator it;

void MainMenu() {
	std::cout << "\n --- Options ---\n";
	std::cout << "    [1] Update Scheduled Payments\n";
	std::cout << "    [2] View Financial Analysis\n";
	std::cout << "\n    [0] Quit\n";
}

int GetOption() {
	int iOpt;
	std::string sOpt = "";
	std::cout << "\nSelect > ";
	std::cin >> sOpt;
	std::regex rgxMainMenu("^[0-9]$");
	if (std::regex_match(sOpt, rgxMainMenu)) {
		return std::stoi(sOpt);
	} else { return 37707; }
}

bool ValidatePaymentName(std::string sName) {
	std::regex rgxName("^[a-zA-Z]{4,15}$");
	if (std::regex_match(sName, rgxName)) {
		return true;
	} else { return false; }
}

bool ValidatePaymentValue(std::string sValue) {
	std::regex rgxValue("^[\\d]{1,7}\\.[\\d]{2}$");
        if (std::regex_match(sValue, rgxValue)) {
		return true;
        } else { return false; }
}

void PaymentsMenu() {
        std::cout << "\n----- Payments: Menu -----\n";
        std::cout << "  1 - Add Payment\n";
        std::cout << "  2 - Update Payment\n";
        std::cout << "  3 - Delete Payment\n";
        std::cout << "\n  0 - Back\n";
}

void AddPayment() {
	std::string sName, sValue;
	bool bInputValid;
	struct Payment oPayment;
	do {
		std::cout << "== Payment Name ==\n";
		std::cout << "  ~ Minimum 4, Maximum 15 Characters\n";
        	std::cout << "  ~ No Numerical or Special Characters\n";
		std::cout << "\nEnter name: ";
		std::cin >> sName;
		if (ValidatePaymentName(sName)) {
			bInputValid = true;
			oPayment.sName = sName;
		} else { bInputValid = false; }
	} while (!bInputValid);
	do {
		std::cout << "\n== Payment Direction ==\n";
		std::cout << "  <1> Inbound\n";
		std::cout << "  <2> Outbound\n";
		std::cout << "\n  <0> Back\n";
		switch(GetOption()) {
			case 0:
				return;
			case 1:
				bInputValid = true;
				oPayment.sDirection = "inbound";
				break;
			case 2:
				bInputValid = true;
				oPayment.sDirection = "outbound";
				break;
			default:
				bInputValid = false;
				std::cout << "\n[!] Unrecognised option.\n";
				break;
		}
	}
	while (!bInputValid);
	do {
		std::cout << "\n== Payment Value ==\n";
		std::cout << "  ~ Min: 0.01 | Max: 9999999.99\n";
		std::cout << "  ~ Numeric characters only\n";
		std::cout << "\nEnter Value: ";
		std::cin >> sValue;
		if (ValidatePaymentValue(sValue)) {
			bInputValid = true;
			oPayment.fValue = std::stof(sValue);
		} else { bInputValid = false; }
	} while (!bInputValid);
	oPayments.push_back(oPayment);
}

void UpdatePayments() {
	PaymentsMenu();
	switch (GetOption()) {
		case 0:
			return;
		case 1:
			AddPayment();
			break;
		case 2:
			std::cout << "[~] Function not yet implemented.\n";
			break;
		case 3:
			std::cout << "[~] Function not yet implemented.\n";
			break;
		default:
			std::cout << "\n[!] Unrecognised option.\n";
			break;
	}
}

void ListPayments() {
	it = oPayments.begin();
	std::cout << "\n== Scheduled Payments ==\n";
	while (it != oPayments.end()) {
		std::cout << "| " << it->sName << " | " << it->sDirection << " | " << it->fValue << " |\n";
		it++;
	}
}

int main() {
	bool bRun = true;

	std::cout << "#####################\n";
	std::cout << "#####  FinCalc  #####\n";
	std::cout << "#####################\n";

	while (bRun) {
		MainMenu();
		switch (GetOption()) {
			case 0:
				std::cout << "[*] Exiting...\n";
				bRun = false;
				break;
			case 1:
				UpdatePayments();
				break;
			case 2:
				ListPayments();
				break;
			default:
				std::cout << "\n[!] Unrecognised option.\n";
				break;
		}
	}
	return 0;
}
