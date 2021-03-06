#pragma once
#include <boost/noncopyable.hpp>

class CTVSet;

// ������������ �� boost::noncopyable - ����� ������ ��������� ����������� � ������������ ����������� ������
class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CTVSet & tv, std::istream & input, std::ostream & output);
	bool HandleCommand();

	// ����������� �� �������������� ����������� � ���, ��� �� �� ������ ������������� �������� ������������
	// CRemoteControl& operator=(const CRemoteControl &) = delete;
private:
	bool TurnOn(std::istream & args);
	bool TurnOff(std::istream & args);
	bool Info(std::istream & args);
private:
	// �������-���������� ������� ������������.
	// ���������� true, ���� ������� ���������� � false, ���� ���� ������
	using Handler = std::function<bool(std::istream& args)>;

	// ���������� �������� ������� �� � ����������
	using ActionMap = std::map<std::string, Handler>;

	CTVSet & m_tv;
	std::istream & m_input;
	std::ostream & m_output;

	const ActionMap m_actionMap;
};

