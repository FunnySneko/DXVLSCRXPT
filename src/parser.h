#include <cstdint>
#include <map>
#include <string>
#include <variant>
#include <vector>

#include "scanner.h"

typedef struct {
	float R;
	float G;
	float B;
	float A;
} RGBA;

typedef std::variant<int64_t, bool> VariableValue;

enum class TextAlignment {
	Left,
	Right,
	Center,
};

enum class FrameKind {
	None,
	Rect,
	StaticTexture,
	AnimatedTexture,
	Collage

};

struct Frame {
	FrameKind Kind;
	union {
		float Border;
		RGBA Color;
		std::string TexturePath;
	} Payload;
};

struct ManagerOptions {
	std::string Name;
	float TextSpeed;
	uint16_t TextSize;
	enum TextAlignment TextAlignment;
	struct Frame Frame;
	std::string DefaultFont;
	std::string AlternativeFont;
};

enum class ActionKind {
	Assign,
	Add,
	Sub,
	Reset,
};

struct Dialogue {
	uint32_t CharacterId;
	std::string DialogueManager;
	std::string Text;
};

struct Action {
	ActionKind Kind;
	std::string Lhs;
	std::variant<int64_t, bool, std::string> Rhs;
};

struct Statement;
struct Options {
	std::string SelectionManger;
	std::vector<std::string> Lines;
};

enum class BranchingPointKind {
	Selection,
	Compare,
};

struct BranchingPoint {
	std::string Name;
	BranchingPointKind Kind;
	std::vector<std::vector<Statement>> Consequences;
};

struct Goto {
	std::string Destination;
};

enum class CmpOp {
	Greater,
	Less,
	GreaterThan,
	LessThan,
};

struct Compare {
	std::variant<int64_t, bool, std::string> Lhs;
	std::variant<int64_t, bool, std::string> Rhs;
};

enum class StatementKind {
	Expr,
	Dialogue,
	Options,
	Goto,
	Compare
};

struct Statement {
	StatementKind Kind;
	union {
		struct Dialogue Dialogue;
		struct Action Action;
	} Statement;
};

struct Script {
	std::vector<Statement> Statements;
};

struct Scenario {
	std::string Name;
	std::map<std::string, VariableValue> consts;
	std::map<std::string, VariableValue> variables;
	ManagerOptions DialogueManger;
	ManagerOptions SelectionManger;
	struct Script Script;
};

class Parser {
private:
	class Scanner Scanner;
	struct Scenario Scenario;

public:
	Parser(class Scanner Scanner) :
		Scanner(Scanner), Scenario({}) {}

	void Parse();
	void ParseConst();

	Token Next() { return Scanner.NextToken(); }
};
