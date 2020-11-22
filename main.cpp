#include <iostream>
#include <list>
#include <string>
#include <regex>

struct Payment {
	std::string sName;
	std::string sDirection;
	float fValue;
};

std::vector<struct Payment> oPayments;
std::vector<struct Payment>::iterator it;

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
	std::regex rgxId("^[0-9]{1,3}$");
	if (std::regex_match(sOpt, rgxId)) {
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

bool ValidatePaymentId(int iId) {
	if (0 <= iId && iId < oPayments.size()) {
		return true;
        } else { return false; }
}

void PaymentsMenu() {
        std::cout << "\n----- Payments: Menu -----\n";
        std::cout << "  1 - Add Payment\n";
        std::cout << "  2 - Edit Payment\n";
        std::cout << "  3 - Delete Payment\n";
	std::cout << "\n  4 - List Payments\n";
        std::cout << "\n  0 - Back\n";
}

void ListPayments() {
        it = std::begin(oPayments);
        std::cout << "\n== Scheduled Payments ==\n";
        std::cout << "| ID | Name | Direction | Amount |\n";
        while (it != std::end(oPayments)) {
                std::cout << "| " << it - oPayments.begin() << " | " << it->sName << " | " << it->sDirection << " | " << it->fValue << " |\n";
                it++;
        }
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

void EditPaymentName() {
	std::string sName;
	std::cout << "\nEnter new name: ";
	std::cin >> sName;
	if (ValidatePaymentName(sName)) {
		it->sName = sName;
	}
}

void EditPayment() {
	int iId;
	bool bInputValid;
	ListPayments();
	do {
		iId = GetOption();
		if (ValidatePaymentId(iId)) {
			bInputValid = true;
			it = oPayments.begin() + iId;
			std::cout << "=== Edit ===\n";
			std::cout << "Payment ID:  " << iId << std::endl;
			std::cout << "[1] Name (" << it->sName << ")\n";
			std::cout << "[2] Direction (" << it->sDirection << ")\n";
			std::cout << "[3] Value (" << it->fValue << ")\n";
			std::cout << "----------\n";
			std::cout << "[0] Back";
			switch (GetOption()) {
				case 0:
					bInputValid = true;
					break;
				case 1:
					EditPaymentName();
					break;
				case 2:
					std::cout << "[~] Function not yet implemented.";
					break;
				case 3:
					std::cout << "[~] Function not yet implemented.";
					break;
				default:
					std::cout << "\n[!] Unrecognised option.\n";
					break;
			}
		} else { bInputValid = false; }
	} while (!bInputValid);
}

void DeletePayment() {
	int iId;
	bool bInputValid;
	ListPayments();
	do {
		iId = GetOption();
		if (ValidatePaymentId(iId)) {
			bInputValid = true;
			it = oPayments.begin() + iId;
			std::cout << "Payment '" << it->sName << "' deleted.\n";
			oPayments.erase(it);
		} else {
			bInputValid = false;
			std::cout << "[!] Payment ID Invalid.\n";
		}
	} while (!bInputValid);
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
			EditPayment();
			break;
		case 3:
			DeletePayment();
			break;
		case 4:
			ListPayments();
			break;
		default:
			std::cout << "\n[!] Unrecognised option.\n";
			break;
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
