#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <GL\freeglut.h>
#include "exprtk.hpp"

char title[] = "OpenGL App";
int oldTimeSinceStart = 0;

float lastRotateX, lastRotateY, lastRotateZ;

float DeltaTime = 0;

const float TARGET_FPS = 60;
const double FRAME_TIME = 1000 / TARGET_FPS;

float Frames = TARGET_FPS * 10;
float FrameID = 0;

GLfloat angleV = 45, fAspect;

void axis(GLfloat nRange) {
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(nRange, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, nRange, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, nRange);
	glEnd();
}

void Normalize(float Vector[3]) {
	float Length = 0;
	for (int i = 0; i < 3; i++)
		Length += pow(Vector[i], 2);

	Length = sqrt(Length);

	if (Length == 0) Length = 1;

	for (int i = 0; i < 3; i++)
		Vector[i] /= Length;
}

void CalculateNormals(float VectorIn[3][3], float Out[]) {
	float Vector1[3], Vector2[3];

	Vector1[0] = VectorIn[0][0] - VectorIn[1][0];
	Vector1[1] = VectorIn[0][1] - VectorIn[1][1];
	Vector1[2] = VectorIn[0][2] - VectorIn[1][2];
	Vector2[0] = VectorIn[1][0] - VectorIn[2][0];
	Vector2[1] = VectorIn[1][1] - VectorIn[2][1];
	Vector2[2] = VectorIn[1][2] - VectorIn[2][2];

	Out[0] = Vector1[1] * Vector2[2] - Vector1[2] * Vector2[1];
	Out[0] = Vector1[2] * Vector2[0] - Vector1[0] * Vector2[2];
	Out[0] = Vector1[0] * Vector2[1] - Vector1[1] * Vector2[0];
	
	Normalize(Out);
}

void CubeWithNormals(float Size) {
	float Normal[3];
	
	glBegin(GL_TRIANGLES);
		{
			float Vertex[3][3] = { { Size, Size, -Size }, { Size, Size, Size }, { Size, -Size, Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { Size, -Size, Size }, { Size, -Size, -Size }, { Size, Size, -Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { -Size, Size, Size }, { -Size, Size, -Size }, { -Size, -Size, Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { -Size, -Size, -Size }, { -Size, -Size, Size }, { -Size, Size, -Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { Size, Size, Size }, { Size, Size, -Size }, { -Size, Size, Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { -Size, Size, -Size }, { -Size, Size, Size }, { Size, Size, -Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { Size, -Size, -Size }, { Size, -Size, Size }, { -Size, -Size, Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { -Size, -Size, Size }, { -Size, -Size, -Size }, { Size, -Size, -Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { Size, -Size, Size }, { Size, Size, Size }, { -Size, Size, Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { -Size, Size, Size }, { -Size, -Size, Size }, { Size, -Size, Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { Size, Size, -Size }, { Size, -Size, -Size }, { -Size, Size, -Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
		{
			float Vertex[3][3] = { { -Size, -Size, -Size }, { -Size, Size, -Size }, { Size, -Size, -Size } };

			CalculateNormals(Vertex, Normal);
			glNormal3fv(Normal);
			glVertex3fv(Vertex[0]);
			glVertex3fv(Vertex[1]);
			glVertex3fv(Vertex[2]);
		}
	glEnd();
}

void setVisParam() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angleV, fAspect, 0.1, 500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 100, 100, 0, 0, 0, 0, 1, 0);
}

void reshape(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;

	glViewport(0, 0, w, h);
	
	fAspect = (GLfloat)w / (GLfloat)h;
	setVisParam();
}

std::vector<std::string> GetDisplayFileSection(std::vector<std::string> Parent, int StartPoint) {
	std::vector<std::string> Result;

	int Current = StartPoint;
	int EndBracketCount = 1;
	while (Current < Parent.size()) {
		if (Parent[Current] == "{") {
			EndBracketCount++;
		} else if (Parent[Current] == "}") {
			EndBracketCount--;

			if (EndBracketCount <= 0)
				break;
		}

		Result.push_back(Parent[Current]);
		Current++;
	}

	return Result;
}

enum DisplayFileObjectType {
	Scene,
	Null,
	Cube,
	Cone,
	Sphere,
	Cylinder,
	Teapot,
	CustomCube,
	Torus,
	Tetrahedron,
	Dodecahedron,
	Octahedron,
	Icosahedron
};

typedef exprtk::expression<float> DisplayFileExpression;
exprtk::symbol_table<float> DisplayFileExpressionSymbolTable;
exprtk::parser<float> DisplayFileExpressionParser;

struct DisplayFile3Axis {
	DisplayFileExpression X;
	DisplayFileExpression Y;
	DisplayFileExpression Z;

	float DefaultX;
	float DefaultY;
	float DefaultZ;

	float AdditionalX;
	float AdditionalY;
	float AdditionalZ;

	float GetX() {
		float CalcVal = X.value();
		return (isnan(CalcVal) ? DefaultX : CalcVal) + AdditionalX;
	}

	float GetY() {
		float CalcVal = Y.value();
		return (isnan(CalcVal) ? DefaultY : CalcVal) + AdditionalY;
	}

	float GetZ() {
		float CalcVal = Z.value();
		return (isnan(CalcVal) ? DefaultZ : CalcVal) + AdditionalZ;
	}

	bool IsDefault() {
		return isnan(X.value()) || isnan(Y.value()) || isnan(Z.value());
	}

	DisplayFile3Axis() {
		DefaultX = DefaultY = DefaultZ = 0;
		AdditionalX = AdditionalY = AdditionalZ = 0;
		X = Y = Z = DisplayFileExpression();
	}

	DisplayFile3Axis(float _DefaultX, float _DefaultY, float _DefaultZ) : DisplayFile3Axis() {
		DefaultX = _DefaultX;
		DefaultY = _DefaultY;
		DefaultZ = _DefaultZ;
	}
};

struct DisplayFileObject {
	DisplayFileObjectType Type = Null;
	DisplayFile3Axis Position = { 0, 0, 0 };
	DisplayFile3Axis Rotation = { 0, 0, 0 };
	DisplayFile3Axis Scale = { 1, 1, 1 };
	DisplayFile3Axis Color = { 0, 0, 1 };

	std::vector<std::string>* AdditionalParameters;
	std::vector<DisplayFileExpression>* AdditionalExpressions;
	std::vector<DisplayFileObject*> Children;

	DisplayFileObject* Parent;

	bool IsVisible = true;

	void SetVisibility(bool NewVisibility) {
		IsVisible = NewVisibility;

		for (int i = 0; i < Children.size(); i++)
			Children[i]->SetVisibility(NewVisibility);
	}
};

void ParseDisplayFileCommands(std::string Input, std::string& Output, std::vector<std::string>* Parameters, std::vector<DisplayFileExpression>* Expressions) {
	Output = "";
	std::string CurrentParam = "";
	
	int Index = 0;
	bool ParamMode = false;
	int EndBracketCount = 1;
	while (Index < Input.size()) {
		if (ParamMode) {
			if (Input[Index] == ',' || Input[Index] == ')') {
				if (Input[Index] == ')') {
					EndBracketCount--;

					if (EndBracketCount > 0) {
						CurrentParam += Input[Index];
						continue;
					}
				}

				DisplayFileExpression Expression;
				Expression.register_symbol_table(DisplayFileExpressionSymbolTable);

				if (!DisplayFileExpressionParser.compile(CurrentParam, Expression))
					Parameters->push_back(CurrentParam);
				else
					Expressions->push_back(Expression);

				CurrentParam = "";
			}
			else if (Input[Index] == '(') {
				EndBracketCount++;
				CurrentParam += Input[Index];
			}
			else
				CurrentParam += Input[Index];
		} else {
			if (Input[Index] == '(')
				ParamMode = true;
			else
				Output += Input[Index];
		}
		
		Index++;
	}
}

DisplayFileObject* ParseDisplayFileSection(std::string Command, std::vector<std::string> Section) {
	DisplayFileObject* ThisSection = new DisplayFileObject();

	if (!Command.empty()) {
		std::string ParsedCommand;
		ThisSection->AdditionalParameters = new std::vector<std::string>();
		ThisSection->AdditionalExpressions = new std::vector<DisplayFileExpression>();
		
		ParseDisplayFileCommands(Command, ParsedCommand, ThisSection->AdditionalParameters, ThisSection->AdditionalExpressions);
		
		if (ParsedCommand == "cube") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 1)
				return new DisplayFileObject();

			ThisSection->Type = Cube;
		} else if (ParsedCommand == "cone") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 4)
				return new DisplayFileObject();

			ThisSection->Type = Cone;
		} else if (ParsedCommand == "cylinder") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 4)
				return new DisplayFileObject();

			ThisSection->Type = Cylinder;
		} else if (ParsedCommand == "sphere") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 3)
				return new DisplayFileObject();

			ThisSection->Type = Sphere;
		} else if (ParsedCommand == "teapot") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 1)
				return new DisplayFileObject();

			ThisSection->Type = Teapot;
		} else if (ParsedCommand == "customcube") {
			if (ThisSection->AdditionalParameters->size() != 0 || ThisSection->AdditionalExpressions->size() != 1)
				return new DisplayFileObject();

			ThisSection->Type = CustomCube;
		} else if (ParsedCommand == "torus") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 4)
				return new DisplayFileObject();

			ThisSection->Type = Torus;
		} else if (ParsedCommand == "tetrahedron") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 0)
				return new DisplayFileObject();

			ThisSection->Type = Tetrahedron;
		} else if (ParsedCommand == "dodecahedron") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 0)
				return new DisplayFileObject();

			ThisSection->Type = Dodecahedron;
		} else if (ParsedCommand == "octahedron") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 0)
				return new DisplayFileObject();

			ThisSection->Type = Octahedron;
		} else if (ParsedCommand == "icosahedron") {
			if (ThisSection->AdditionalParameters->size() != 1 || ThisSection->AdditionalExpressions->size() != 0)
				return new DisplayFileObject();

			ThisSection->Type = Icosahedron;
		} else if (ParsedCommand == "scene") {
			ThisSection->Type = Scene;
		}
	}

	for (int i = 0; i < static_cast<int>(Section.size()); i++) {
		if (Section[i] == "{") {
			std::vector<std::string> InnerSection = GetDisplayFileSection(Section, i + 1);

			DisplayFileObject* Child = ParseDisplayFileSection(Section[i - 1], InnerSection);
			Child->Parent = ThisSection;
			
			if (Child->Type != Scene)
				ThisSection->Children.push_back(Child);
			
			i += InnerSection.size() + 1;
		}
		else if (Section[i] == "}")
			continue;
		else {
			if (i + 1 < Section.size() && Section[i + 1] == "{")
				continue;

			std::string ParsedCommand;
			std::vector<std::string>* Parameters = new std::vector<std::string>();
			std::vector<DisplayFileExpression>* Expressions = new std::vector<DisplayFileExpression>();
			
			ParseDisplayFileCommands(Section[i], ParsedCommand, Parameters, Expressions);

			if (ThisSection->Type == Scene) {
				if (Expressions->size() != 1)
					continue;

				if (ParsedCommand == "frames")
					Frames = Expressions->at(0).value();
			} else {
				if (Parameters->size() != 0 && Expressions->size() != 3)
					continue;

				if (ParsedCommand == "translate") {
					ThisSection->Position.X = Expressions->at(0);
					ThisSection->Position.Y = Expressions->at(1);
					ThisSection->Position.Z = Expressions->at(2);
				} else if (ParsedCommand == "rotate") {
					ThisSection->Rotation.X = Expressions->at(0);
					ThisSection->Rotation.Y = Expressions->at(1);
					ThisSection->Rotation.Z = Expressions->at(2);
				} else if (ParsedCommand == "scale") {
					ThisSection->Scale.X = Expressions->at(0);
					ThisSection->Scale.Y = Expressions->at(1);
					ThisSection->Scale.Z = Expressions->at(2);
				} else if (ParsedCommand == "color") {
					ThisSection->Color.X = Expressions->at(0);
					ThisSection->Color.Y = Expressions->at(1);
					ThisSection->Color.Z = Expressions->at(2);
				}
			}
		}
	}

	return ThisSection;
}

const char* LastLoadedDisplayFile;
DisplayFileObject* LoadedDisplayFile;

void LoadDisplayFile(const char* FileName) {
	printf("Loading File: %s\n", FileName);
	
	LastLoadedDisplayFile = FileName;
	
	std::ifstream inStream;
	inStream.open(FileName);
	
	if (!inStream)
		return;

	std::vector<std::string> Instructions;
	std::string CurrentInstruction = "";

	char ReadChar;
	int AmountOfBrackets = 0;
	while (inStream >> ReadChar) {
		if (CurrentInstruction.empty()) {
			CurrentInstruction += ReadChar;

			if (CurrentInstruction == "{" || CurrentInstruction == "}") {
				Instructions.push_back(CurrentInstruction);
				CurrentInstruction = "";
			}
		} else  {
			CurrentInstruction += ReadChar;

			if (ReadChar == '(') {
				AmountOfBrackets++;
			} else if (ReadChar == ')') {
				AmountOfBrackets--;

				if (AmountOfBrackets > 0)
					continue;
				
				Instructions.push_back(CurrentInstruction);
				CurrentInstruction = "";
			}
		}
	}

	inStream.close();

	LoadedDisplayFile = ParseDisplayFileSection("", Instructions);

	printf("Display Filed Loaded.\n");
}

void LoadDisplayFile() {
	LoadDisplayFile(LastLoadedDisplayFile);
}


bool Playing = true;

std::vector<int> SelectionModeLevels;
bool SelectionMode = false;

void update(int x) {
	const int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	DeltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;

	if (Playing) {
		FrameID++;

		if (FrameID > Frames)
			FrameID = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(FRAME_TIME, update, 0);
}

void RecursiveBuildObjectIndex(std::vector<int>* IndexList, DisplayFileObject* Object) {
	if (Object->Parent == nullptr)
		return;

	for (int i = 0; i < Object->Parent->Children.size(); i++)
		if (Object->Parent->Children[i] == Object) {
			IndexList->insert(IndexList->begin(), i);
			break;
		}

	RecursiveBuildObjectIndex(IndexList, Object->Parent);
}

bool ObjectIsSelected(DisplayFileObject* Object) {
	std::vector<int>* IndexList = new std::vector<int>();
	RecursiveBuildObjectIndex(IndexList, Object);

	bool AllLevelsCorrect = true;
	
	for (int i = 0; i < SelectionModeLevels.size(); i++) {
		if (i >= IndexList->size()) {
			break;
		} else if (SelectionModeLevels[i] != IndexList->at(i)) {
			AllLevelsCorrect = false;
			break;
		}
	}
	
	return AllLevelsCorrect;
}

void renderObject(DisplayFileObject* Object) {
	glPushMatrix();
		glTranslatef(Object->Position.GetX(), Object->Position.GetY(), Object->Position.GetZ());
		glRotatef(Object->Rotation.GetX(), 1, 0, 0);
		glRotatef(Object->Rotation.GetY(), 0, 1, 0);
		glRotatef(Object->Rotation.GetZ(), 0, 0, 1);
		glScalef(Object->Scale.GetX(), Object->Scale.GetY(), Object->Scale.GetZ());

		bool IsSelected = SelectionMode && ObjectIsSelected(Object);
	
		if (IsSelected)
			glColor4f(0, 2, 0, 0.5);
		else
			if (!Object->Color.IsDefault())
				glColor3f(Object->Color.GetX(), Object->Color.GetY(), Object->Color.GetZ());

		if (Object->IsVisible || IsSelected) {
			switch (Object->Type) {
				case Null: break;
				case Cube: {
					float Size = Object->AdditionalExpressions->at(0).value();

					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidCube(Size);
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireCube(Size);
				} break;
				case Cone: {
					float Base = Object->AdditionalExpressions->at(0).value();
					float Height = Object->AdditionalExpressions->at(1).value();
					float Slices = Object->AdditionalExpressions->at(2).value();
					float Stacks = Object->AdditionalExpressions->at(3).value();

					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidCone(Base, Height, Slices, Stacks);
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireCone(Base, Height, Slices, Stacks);
				} break;
				case Sphere: {
					float Radius = Object->AdditionalExpressions->at(0).value();
					float Slices = Object->AdditionalExpressions->at(2).value();
					float Stacks = Object->AdditionalExpressions->at(2).value();

					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidSphere(Radius, Slices, Stacks);
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireSphere(Radius, Slices, Stacks);
				} break;
				case Cylinder: {
					float Radius = Object->AdditionalExpressions->at(0).value();
					float Height = Object->AdditionalExpressions->at(1).value();
					float Slices = Object->AdditionalExpressions->at(2).value();
					float Stacks = Object->AdditionalExpressions->at(3).value();

					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidCylinder(Radius, Height, Slices, Stacks);
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireCylinder(Radius, Height, Slices, Stacks);
				} break;
				case Teapot: {
					float Size = Object->AdditionalExpressions->at(0).value();

					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidTeapot(Size);
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireTeapot(Size);
				} break;
				case CustomCube: {
					float Size = Object->AdditionalExpressions->at(0).value();

					CubeWithNormals(Size);
				} break;
				case Torus: {
					float InnerRadius = Object->AdditionalExpressions->at(0).value();
					float OuterRadius = Object->AdditionalExpressions->at(1).value();
					float Slices = Object->AdditionalExpressions->at(2).value();
					float Stacks = Object->AdditionalExpressions->at(3).value();

					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidTorus(InnerRadius, OuterRadius, Slices, Stacks);
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireTorus(InnerRadius, OuterRadius, Slices, Stacks);
				} break;
				case Tetrahedron: {
					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidTetrahedron();
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireTetrahedron();
				} break;
				case Dodecahedron: {
					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidDodecahedron();
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireDodecahedron();
				} break;
				case Octahedron: {
					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidOctahedron();
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireOctahedron();
				} break;
				case Icosahedron: {
					if (Object->AdditionalParameters->at(0) == "solid")
						glutSolidIcosahedron();
					else if (Object->AdditionalParameters->at(0) == "wireframe")
						glutWireIcosahedron();
				} break;
			}
		}
		
		for (int i = 0; i < Object->Children.size(); i++)
			renderObject(Object->Children[i]);
	glPopMatrix();
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(lastRotateX, 1, 0, 0);
	glRotatef(lastRotateY, 0, 1, 0);
	glRotatef(lastRotateZ, 0, 0, 1);

	axis(20);
	renderObject(LoadedDisplayFile);
	glPopMatrix();

	glutSwapBuffers();
}

bool LightingEnabled = true;

void processKeyboardInput(unsigned char key, int x, int y) {
	switch (key) {
		case 'l': {
			if (LightingEnabled)
				glDisable(GL_LIGHTING);
			else
				glEnable(GL_LIGHTING);

			LightingEnabled = !LightingEnabled;
		} break;
		case 'r': {
			SelectionMode = false;
			SelectionModeLevels.clear();
			
			LoadDisplayFile();
		} break;
		case 'o': {
			SelectionMode = !SelectionMode;
			SelectionModeLevels.clear();

			if (SelectionMode && LoadedDisplayFile->Children.size() > 0)
				SelectionModeLevels.push_back(0);
		} break;
		case 'w': lastRotateX += DeltaTime; break;
		case 's': lastRotateX -= DeltaTime; break;
		case 'a': lastRotateY += DeltaTime; break;
		case 'd': lastRotateY -= DeltaTime; break;
		case 'q': angleV += DeltaTime * 0.5f; setVisParam(); break;
		case 'e': angleV -= DeltaTime * 0.5f; setVisParam(); break;
		case ' ': Playing = !Playing; break;
	}
}

DisplayFileObject* FindSelectedObjectParent() {
	DisplayFileObject* SelectedObject = LoadedDisplayFile;
	for (int i = 0; i < SelectionModeLevels.size() - 1; i++)
		SelectedObject = SelectedObject->Children[SelectionModeLevels[i]];
	return SelectedObject;
}

void processKeyboardSpecialInput(int key, int x, int y) {
	if (!SelectionMode)
		return;

	DisplayFileObject* SelectedObjectParent = FindSelectedObjectParent();
	int SelectedChild = SelectionModeLevels.back();
	DisplayFileObject* SelectedObject = SelectedObjectParent->Children[SelectedChild];
	
	switch (key) {
		case GLUT_KEY_UP: {
			SelectedObject->Position.AdditionalY += DeltaTime * 0.05f;
		} break;
		case GLUT_KEY_DOWN: {
			SelectedObject->Position.AdditionalY -= DeltaTime * 0.05f;
		} break;
		case GLUT_KEY_LEFT: {
			SelectedObject->Position.AdditionalX += DeltaTime * 0.05f;
		} break;
		case GLUT_KEY_RIGHT: {
			SelectedObject->Position.AdditionalX -= DeltaTime * 0.05f;
		} break;
		case GLUT_KEY_END: {
			SelectedObject->SetVisibility(!SelectedObject->IsVisible);
		} break;
		case GLUT_KEY_PAGE_DOWN: {
			if (SelectedObject->Children.size() <= 0)
				return;

			SelectionModeLevels.push_back(0);
		} break;
		case GLUT_KEY_PAGE_UP: {
			SelectionModeLevels.pop_back();
		} break;
		case GLUT_KEY_CTRL_R: {
			SelectedChild++;

			if (SelectedChild >= SelectedObjectParent->Children.size())
				SelectedChild = 0;

			SelectionModeLevels.back() = SelectedChild;
		} break;
	}
}

int main(int argc, char** argv) {
	printf("-> Visualizador OpenGL\n");
	printf("--> Trabalho  de  Construção Software Grafico 3D\n");
	printf("--> Aluno: Alan Renato Bunese, Turma U\n");
	printf("\nPara Abrir uma Cena, basta abrir a aplicacao com o Arquivo. (Drag and Drop)\n");
	printf("\nControles:\n");
	printf("W, A, S, D - Rotacionar Camera ao redor do Centro da Cena. (0, 0, 0)\n");
	printf("Barra de Espaço - Pausar/Continuar Animacao.\n");
	printf("Q, E - Zoom +/-.\n");
	printf("R - Recarregar ultima Cena.\n");
	printf("L - Ativar/Desativar Iluminacao.\n");
	printf("O - Ativar/Desativar Modo de Objeto.\n");
	printf("\nControles Adicionais no Modo de Objeto:\n");
	printf("Setas do Teclado - Mover Grupo de Objetos Selectionados.\n");
	printf("CTRL Direito - Circular entre Objetos Disponiveis.\n");
	printf("Page Down - Entrar 1 Nivel na Hierarquia de Objetos.\n");
	printf("Page Up - Sair 1 Nivel na Hierarquia de Objetos.\n");
	printf("END - Ativar/Desativar Visualizacao do Grupo de Objetos Selectionados.\n");
	
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(title);
	glClearColor(0, 0, 0, 1.0f);
	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);

	GLfloat specular[4] = { 0.5, 0.5, 0.5, 1 };
	GLint shininess = 10;
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMateriali(GL_FRONT, GL_SHININESS, shininess);

	GLfloat ambientLight[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat diffuseLight[4] = { 0.7,0.7,0.7,1.0 };
	GLfloat specularLight[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lightPositions[4] = { 0.0, 50.0, 50.0, 1.0 };
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositions);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processKeyboardInput);
	glutSpecialFunc(processKeyboardSpecialInput);
	glutTimerFunc(FRAME_TIME, update, 0);
	
	DisplayFileExpressionSymbolTable.add_variable("DeltaTime", DeltaTime);
	DisplayFileExpressionSymbolTable.add_variable("Frame", FrameID);
	DisplayFileExpressionSymbolTable.add_variable("Frames", Frames);
	
	DisplayFileExpressionSymbolTable.add_constant("TargetFPS", TARGET_FPS);

	LoadedDisplayFile = new DisplayFileObject();
	
	if (argc > 1)
		LoadDisplayFile(argv[1]);
		
	
	glutMainLoop();
	return 0;
}

