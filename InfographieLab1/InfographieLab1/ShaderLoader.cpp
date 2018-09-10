#include "ShaderLoader.h"
#include <fstream>
#include <vector>


ShaderLoader::ShaderLoader()
{
}

string ShaderLoader::ReadShader(char* filename) 
{
	string shaderCode;

	ifstream file(filename, std::ios::in);

	if (!file.good()) 
	{
		cout << "Lecture impossible du fichier " << filename << endl;
	}
	file.seekg(0, ios::end);
	shaderCode.resize(file.tellg());

	file.seekg(0, ios::beg);
	file.read(&shaderCode[0], shaderCode.size());

	file.close();

	return shaderCode;
}


GLuint ShaderLoader::CreateShader(GLenum shaderType, string source, char* shaderName) 
{
	int compileResult = 0;

	GLuint shader = glCreateShader(shaderType);
	
	const char *SHADER_CODE_PTR = source.c_str();
	const int SHADER_CODE_SIZE = source.size();

	glShaderSource(shader, 1, &SHADER_CODE_PTR, &SHADER_CODE_SIZE);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE) 
	{
		int infoLogLength = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		cout << "Erreur durant le compilage du shader: " << shaderName << endl << &shaderLog[0] << endl;
		return 0;
	}
	return shader;

}

GLuint ShaderLoader::CreateProgram(char* vertexShaderFilename, char* fragmentShaderFilename)
{
	//Appelle les fonctions de lecture des fichiers de shaders   
	string vertex_shader_code = ReadShader(vertexShaderFilename);      
	string fragment_shader_code = ReadShader(fragmentShaderFilename);  
	//Crée et compile les shaders 
	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, _strdup(vertex_shader_code.c_str()) , (char*)"vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, _strdup(fragment_shader_code.c_str()) , (char*)"fragment shader");
	int link_result = 0;     
	//Crée le handle du programme et le lie aux shaders compilés     
	GLuint program = glCreateProgram();    
	glAttachShader(program, vertex_shader);     
	glAttachShader(program, fragment_shader);       
	//Lie l’objet programme pour crée un executable qui sera traité par le GPU 
	glLinkProgram(program);    
	glGetProgramiv(program, GL_LINK_STATUS, &link_result); 

   //Valide si la liaison a bien fonctionné 
	if (link_result == GL_FALSE)     
	{        
		int info_log_length = 0;        
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);        
		vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl; 
		return 0;      
	} 
	return program;

}