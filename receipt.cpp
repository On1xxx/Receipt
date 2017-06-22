
#include "receipt.hpp"
#include "messages.hpp"
#include <algorithm>

/*****************************************************************************/
Receipt::Receipt(std::string _Pname, int _Anumber)
{
	if (_Pname.empty())
		throw std::logic_error(Messages::EmptyPayerName);
	else if (_Anumber <= 0)
		throw std::logic_error(Messages::InvalidAccountNumber);
	else
	{
		PayerName = _Pname;
		AccountNumber = _Anumber;
	}
}

/*****************************************************************************/

void Receipt::addService(std::string _Sname)
{
	if (_Sname.empty())
		throw std::logic_error(Messages::EmptyServiceName);
	if (hasService(_Sname))
		throw std::logic_error(Messages::DuplicatedService);

	Servise.insert(std::make_pair(_Sname, (std::make_pair(0.0, 0.0))));

	counter++;
}

/*****************************************************************************/

bool Receipt::hasServices() const
{
	return (counter > 0);
}

/*****************************************************************************/

bool  Receipt::hasService(std::string _Sname) const
{
	return (Servise.find(_Sname) == Servise.end()) ? false : true;
}

/*****************************************************************************/

void Receipt::removeService(std::string _Sname)
{
	IsValid(_Sname);

	Servise.erase(_Sname);


	counter--;
}

/*****************************************************************************/

void Receipt::renameService(std::string _Sname, std::string _REname)
{
	if (_Sname.empty())
		throw std::logic_error(Messages::EmptyServiceName);
	else if (_REname.empty())
		throw std::logic_error(Messages::EmptyServiceName);
	else if (!hasService(_Sname))
		 throw std::logic_error(Messages::ServiceDoesNotExist);
	else if (hasService(_REname))
		throw std::logic_error(Messages::DuplicatedService);

	double temp1;
	double temp2;
	temp1 = Servise.find(_Sname)->second.first;
	temp2 = Servise.find(_Sname)->second.second;

	
	
	Servise.erase(_Sname);
	Servise.erase(_Sname);

	insertServise(_REname, temp1, temp2);


}

/*****************************************************************************/

void Receipt::insertServise(std::string _Sname, double _Debt, double _Paid)
{
	Servise.insert(std::make_pair(_Sname, std::make_pair(_Debt, _Paid)));
}

/*****************************************************************************/

bool Receipt::IsValid(std::string _Sname) const
{
	if ( _Sname.empty() )
		throw std::logic_error(Messages::EmptyServiceName);
	else if (!hasService(_Sname))
		throw std::logic_error(Messages::ServiceDoesNotExist);
	else return true;
}

/*****************************************************************************/

void Receipt::trackDebt(std::string _Sname, double _NewP)
{
	IsValid(_Sname);

	Servise.find(_Sname)->second.first += _NewP;
}

/*****************************************************************************/

void Receipt::trackPay(std::string _Sname, double _NewP)
{
	IsValid(_Sname);
	if (_NewP < 0)
		throw std::logic_error(Messages::InvalidAmountValue);

	Servise.find(_Sname)->second.second += _NewP;
}

/*****************************************************************************/

double Receipt::getTotalDebt() const
{
	double Temp = 0;


	for (auto it = Servise.begin(); it != Servise.end(); it++)
		Temp += it->second.first;

	return Temp;
}

/*****************************************************************************/

double Receipt::getTotalPaid() const
{
	double Temp = 0;


	for (auto it = Servise.begin(); it != Servise.end(); it++)
		Temp += it->second.second;

	return Temp;
}

/*****************************************************************************/

std::vector < std::string> Receipt::fetchOverpaid() const
{
	std::vector<std::string> Result;
	for (auto it = Servise.begin(); it != Servise.end(); it++)
	{
		if (it->second.first < 0)
			Result.push_back(it->first);
	}

	return Result;
}

/*****************************************************************************/

std::vector < std::string> Receipt::fetchUnderpaid() const
{
	std::vector<std::string> Result;
	for (auto it = Servise.begin(); it != Servise.end(); it++)
	{
		if (it->second.first > 0)
			Result.push_back(it->first);
	}

	return Result;
}

/*****************************************************************************/

void Receipt::forEachService(std::function< void(const std::string &, double, double)> Function)const
{
	std::for_each
		(
			Servise.begin(), Servise.end(),
			[&Function](const std::pair <std::string, std::pair<double, double> > & cell)
	{
		Function(cell.first, cell.second.first, cell.second.second);
	}
	);
}

/*****************************************************************************/