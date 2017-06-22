#ifndef _RECEIPT_HPP_
#define _RECEIPT_HPP_

/*****************************************************************************/

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>


/*****************************************************************************/

class Receipt
{



	std::string PayerName;
	int AccountNumber;
	int counter = 0;

	std::map <std::string, std::pair < double, double> >  Servise;

	

	
 
public:

	Receipt ( std::string _Pname, int _Anumber);

	Receipt(const Receipt &) = delete;
	Receipt & operator = (const Receipt &) = delete;

	std::string getPayerName() const;
	int getAccountNumber() const;
	int getServicesCount() const;

	bool hasServices() const;

	bool hasService(std::string _Sname) const;
	void addService(std::string _Sname);
	double getDebtAmount(std::string _Sname) const;
	double getPaidAmount(std::string _Sname) const;
	void removeService(std::string _Sname);
	void renameService(std::string _Sname, std::string _REname);
	void insertServise(std::string _Sname, double _Debt, double _Paid);
	bool IsValid(std::string _Sname) const;
	void trackDebt(std::string _Sname, double _NewP);
	void trackPay(std::string _Sname, double _NewP);
	double getTotalDebt() const;
	double getTotalPaid() const;
	std::vector < std::string> fetchOverpaid() const;
	std::vector < std::string> fetchUnderpaid() const;
	void forEachService(std::function< void(const std::string &, double, double)> Function) const;
	
};


	inline std::string Receipt::getPayerName() const
{
	return PayerName;
}


	inline int Receipt::getAccountNumber() const
{
	return AccountNumber;
}

	inline int Receipt::getServicesCount() const
	{
		return counter;
	}


	inline double Receipt::getDebtAmount(std::string _Sname) const
	{
		if (IsValid(_Sname))
		return Servise.find(_Sname)->second.first;
	}

	inline double Receipt::getPaidAmount(std::string _Sname) const
	{

		if (IsValid(_Sname))
			
			return Servise.find(_Sname)->second.second;
	}

#endif // _RECEIPT_HPP_