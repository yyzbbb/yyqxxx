#include<iostream>
#include<string>
using namespace std;
bool negative_1 = 0, negative_2 = 0, negative_0 = 0;
string str1, str2;

struct node
{
	string num;
	node* next;
};

node* input_number(string a)
{
	int len = a.length();
	node* head = new node;
	node* pre = head;

	for (int i = len - 1; i >= 0; i--)
	{
		node* p = new node;
		p->num = a[i];
		pre->next = p;
		pre = p;
		p->next = NULL;
	}
	return head;
}

void get_number()
{
	cin >> str1;
	cin >> str2;

	if (str1[0] == '-')
	{
		negative_1 = true;
		str1 = str1.erase(0, 1);
	}
	if (str2[0] == '-')
	{
		negative_2 = true;
		str2 = str2.erase(0, 1);
	}

	int t;
	while ((t = str1.find(',')) != string::npos)
	{
		str1 = str1.erase(t, 1);
	}
	while ((t = str2.find(',')) != string::npos)
	{
		str2 = str2.erase(t, 1);
	}
	int intstart1 = str1.find('.');
	int intstart2 = str2.find('.');
	int len1 = str1.length();
	int len2 = str2.length();
	int doublestart1 = 0, doublestart2 = 0;
	if (intstart1 == -1 && intstart2 == -1)
	{
		intstart1 = len1; intstart2 = len2;
		doublestart1 = len1 - intstart1; doublestart2 = len2 - intstart2;
		
	}
	else if (intstart1 != -1 && intstart2 != -1)
	{
		doublestart1 = len1 - intstart1; doublestart2 = len2 - intstart2;
	}
	else if (intstart1 == -1 && intstart2 != -1)
	{
		intstart1 = len1;
		str1 = str1 + '.';
		doublestart1 = len1 + 1 - intstart1;
		doublestart2 = len2 - intstart2;
	}
	else if (intstart1 != -1 && intstart2 == -1)
	{
		intstart2 = len2;
		str2 = str2 + '.';
		doublestart1 = len1 - intstart1;
		doublestart2 = len2 + 1 - intstart2;
	}
	
	int q = 0;
	if (intstart1 > intstart2)
	{
		q = intstart1 - intstart2;
		while (q--)
		{
			str2 = '0' + str2;
		}
	}
	else if (intstart1 < intstart2)
	{
		q = intstart2 - intstart1;
		while (q--)
		{
			str1 = '0' + str1;
		}
	}

	int p = 0;
	if (doublestart1 > doublestart2)
	{
		p = doublestart1 - doublestart2;
		while (p--)
		{
			str2 = str2 + '0';
		}
	}
	else
	{
		p = doublestart2 - doublestart1;
		while (p--)
		{
			str1 = str1 + '0';
		}
	}
}

void add_number(node* a, node* b, node* rst)
{
	node* p1 = a->next;
	node* p2 = b->next;
	node* pre = rst;
	int up = 0;
	int temp = 0;
	while (p1 != NULL && p2 != NULL)
	{
		node* p0 = new node;
		pre->next = p0;
		pre = p0;
		p0->next = NULL;
		if (p1->num == "." && p2->num == ".")
		{
			p1 = p1->next; p2 = p2->next; p0->num = ".";
		}
		else
		{
			int temp1 = stoi(p1->num);
			int temp2 = stoi(p2->num);
			if (temp1 + temp2 + up < 10)
			{
				p0->num = to_string(temp1 + temp2 + up);
				up = 0;
			}
			else
			{
				p0->num = to_string(temp1 + temp2 + up - 10);
				up = 1;
			}
			p1 = p1->next; p2 = p2->next;
		}
	}
	if (up == 1)
	{
		node* p0 = new node;
		p0->num = "1";
		pre->next = p0;
		p0->next = NULL;
	}
}

void sub_number(node* a, node* b, node* rst)
{
	node* n1 = a->next;
	node* n2 = b->next;
	node* pre = rst;
	int up = 0;
	while (n1 != NULL && n2 != NULL)
	{
		node* n0 = new node;
		pre->next = n0;
		pre = n0;
		n0->next = NULL;
		if (n1->num == "." && n2->num == ".")
		{
			n1 = n1->next; n2 = n2->next; n0->num = ".";
		}
		else
		{
			int temp1 = stoi(n1->num);
			int temp2 = stoi(n2->num);
			if (up + temp1 - temp2 >= 0)
			{
				n0->num = to_string(up + temp1 - temp2);
				up = 0;
			}
			else
			{
				n0->num = to_string(up + temp1 - temp2 + 10);
				up = -1;
			}
			n1 = n1->next; n2 = n2->next;
		}
	}
}

bool compare_number(string a, string b)
{
	int len1 = a.length();
	int len2 = b.length();
	if (len1 > len2)
	{
		return true;
	}
	else if (len2 > len1)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < len1; i++)
		{
			if (a[i] - b[i] > 0) { return true; }
			else if (a[i] - b[i] < 0) { return false; }
		}return false;
	}
}

void print_number(node* rst, string a, string b, bool flag = false)
{
	string result; int count = 0;
	while (rst->next != NULL)
	{
		rst = rst->next;
		int ajdg = a.find(".");
		int bjdg = b.find(".");
		if (ajdg == -1 && bjdg == -1)
		{
			if (count == 3)
			{
				result = "," + result; count = 0;
			}
			result = rst->num + result;
			count++;
		}
		else
		{
			int rstjdg = result.find(".");
			int rstlen = result.length();
			if (rstjdg == -1)
			{
				result = rst->num + result;
			}
			else if (rstlen != 0 && rstjdg == rstlen)
			{
				result = rst->num + result;
			}
			else if (rstjdg < rstlen)
			{
				if (count == 3)
				{
					result = "," + result; count = 0;
				}
				result = rst->num + result;
				count++;
			}
		}
	}
	int m = result.length();
	int point = result.find('.');
	while ((result[0] == '0' && point != 1) || result[0] == ',')
	{
		if (m == 1)break;
		result.erase(0, 1);
		m--;
		point = result.find('.');
	}
	int pointjdg = result.find('.');
	if (pointjdg != -1)
	{
		while (m != 1 && result[m - 1] == '0')
		{
			result.erase(m - 1, 1);
			m--;
			if (result[m - 1] == '.')
			{
				result.erase(m - 1, 1);
				break;
			}
			if (result[m - 1] != '.' && result[m - 1] != '0')break;
		}
	}

	if (flag == true && result != "0")cout << "-";
	cout << result << endl;
}

int main()
{
	long num;
	cin >> num;
	while (num--)
	{
		str1.erase(0); str2.erase(0);
		negative_1 = 0; negative_2 = 0; negative_0 = 0;
		char symbol;
		cin >> symbol;
		get_number();
		node* q1 = input_number(str1);
		node* q2 = input_number(str2);
		node* q0 = new node;
		q0->next = NULL;
		if ((symbol == '+' && !negative_1 && !negative_2) || (symbol == '-' && !negative_1 && negative_2))
		{
			add_number(q1, q2, q0);
			print_number(q0, str1, str2);
		}
		else if ((symbol == '+' && negative_1 && negative_2) || (symbol == '-' && negative_1 && !negative_2))
		{
			negative_0 = true;
			add_number(q1, q2, q0);
			print_number(q0, str1, str2, negative_0);
		}
		else if ((symbol == '-' && !negative_1 && !negative_2) || (symbol == '+' && !negative_1 && negative_2))
		{
			bool comp = compare_number(str1, str2);
			if (comp)
			{
				sub_number(q1, q2, q0);
				print_number(q0, str1, str2);
			}
			else
			{
				negative_0 = true;
				sub_number(q2, q1, q0);
				print_number(q0, str1, str2, negative_0);
			}
		}
		else if ((symbol == '+' && negative_1 && !negative_2) || (symbol == '-' && negative_1 && negative_2))
		{
			bool comp = compare_number(str1, str2);
			if (comp)
			{

				negative_0 = true;
				sub_number(q1, q2, q0);
				print_number(q0, str1, str2, negative_0);
			}
			else
			{
				sub_number(q2, q1, q0);
				print_number(q0, str1, str2);
			}
		}
	}
}





