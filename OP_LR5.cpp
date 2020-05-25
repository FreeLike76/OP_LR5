#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;


//	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	Headers for functions
string infixToPostfix(const std::string& infix);
bool is_operator(string a);
//	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	Node struct
struct Node
{
	string data;
	Node* left;
	Node* right;
	Node(string data)
	{
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
};
//	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	Tree Class
class StList
{
private:
	void readTreeUtil(Node* cur)
	{
		if (cur->left != nullptr)
			readTreeUtil(cur->left);
		if (cur->right != nullptr)
			readTreeUtil(cur->right);
		cout << cur->data << endl;
	}
public:
	vector<Node*> parts;
	void buildExpr(string postf)
	{
		string temp;
		vector<Node* > stack;
		for (int i = 0; i < postf.size(); i++)
		{
			if (postf[i] != ' ')
			{
				temp += postf[i];
			}
			else if (!is_operator(temp))
			{
				Node* a = new Node(temp);
				stack.push_back(a);
				temp.clear();
			}
			else
			{
				Node* a = new Node(temp);
				a->left = stack.back();
				stack.pop_back();
				a->right = stack.back();
				stack.pop_back();
				stack.push_back(a);
				temp.clear();
			}
		}
		parts.push_back(stack.front());
	}
	void readTree(int index)
	{
		readTreeUtil(parts[index]);
	}
};
//	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	MAIN
int main() {
	string infix = "a = 3 + 4 * 7";
	cout << "infix:   " << infix << '\n';
	cout << "postfix: " << infixToPostfix(infix) << '\n';
	StList Tree;
	Tree.buildExpr(infixToPostfix(infix));
	Tree.readTree(0);

	return 0;
}

//	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	=	Functions

string infixToPostfix(const std::string& infix) {
	const std::string ops = "=-+/*^";
	std::stringstream ss;
	std::stack<int> s;

	std::stringstream input(infix);
	std::string token;
	while (std::getline(input, token, ' ')) {
		if (token.empty()) {
			continue;
		}

		char c = token[0];
		size_t idx = ops.find(c);

		// check for operator
		if (idx != std::string::npos) {
			while (!s.empty()) {
				int prec2 = s.top() / 2;
				int prec1 = idx / 2;
				if (prec2 > prec1 || (prec2 == prec1 && c != '^')) {
					ss << ops[s.top()] << ' ';
					s.pop();
				}
				else break;
			}
			s.push(idx);
		}
		else if (c == '(') {
			s.push(-2); // -2 stands for '('
		}
		else if (c == ')') {
			// until '(' on stack, pop operators.
			while (s.top() != -2) {
				ss << ops[s.top()] << ' ';
				s.pop();
			}
			s.pop();
		}
		else {
			ss << token << ' ';
		}
	}

	while (!s.empty()) {
		ss << ops[s.top()] << ' ';
		s.pop();
	}

	return ss.str();
}

bool is_operator(string a)
{
	if (a == "=" || a == "+" || a == "-" || a == "*" || a == "/" || a == "^")
		return true;
	return false;
}