#include "Shader.hpp"
#include "ScriptError.hpp"
#include <fstream>
#include <sstream>
namespace S2VX {
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath) {
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// if geometry shader path is present, also load a geometry shader
			if (geometryPath != "") {
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::ifstream::failure e) {
			//throw ScriptError("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		//vertex = glCreateShader(GL_VERTEX_SHADER);
		//glShaderSource(vertex, 1, &vShaderCode, NULL);
		//glCompileShader(vertex);
		//checkCompileErrors(vertex, "VERTEX");
		//// fragment Shader
		////fragment = glCreateShader(GL_FRAGMENT_SHADER);
		////glShaderSource(fragment, 1, &fShaderCode, NULL);
		////glCompileShader(fragment);
		//checkCompileErrors(fragment, "FRAGMENT");
		//// if geometry shader is given, compile geometry shader
		//unsigned int geometry;
		////if (geometryPath != "") {
		//	const char* gShaderCode = geometryCode.c_str();
		//	geometry = glCreateShader(GL_GEOMETRY_SHADER);
		//	glShaderSource(geometry, 1, &gShaderCode, NULL);
		//	glCompileShader(geometry);
		//	checkCompileErrors(geometry, "GEOMETRY");
		//}
		//// shader Program
		//program = glCreateProgram();
		//glAttachShader(program, vertex);
		//glAttachShader(program, fragment);
		//if (geometryPath != "")
		//	glAttachShader(program, geometry);
		//glLinkProgram(program);
		//checkCompileErrors(program, "PROGRAM");
		//// delete the shaders as they're linked into our program now and no longer necessery
		//glDeleteShader(vertex);
		//glDeleteShader(fragment);
		//if (geometryPath != "") {
		//	glDeleteShader(geometry);
		//}
	}
	Shader::~Shader() {
		/*glDeleteProgram(program);*/
	}
	Shader::Shader(Shader&& other)
		: program{ other.program } {
		program = 0;
	}
	Shader& Shader::operator=(Shader&& other) {
		if (this != &other) {
			program = other.program;
			other.program = 0;
		}
		return *this;
	}
	void Shader::checkCompileErrors(const GLuint shader, const std::string& type) {
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				throw ScriptError("ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ");
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				throw ScriptError("ERROR::PROGRAM_LINKING_ERROR of type: " + type + "\n" + infoLog + "\n -- --------------------------------------------------- -- ");
			}
		}
	}
	void Shader::setBool(const std::string &name, const bool value) const {
		glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
	}
	void Shader::setInt(const std::string &name, const int value) const {
		glUniform1i(glGetUniformLocation(program, name.c_str()), value);
	}
	void Shader::setFloat(const std::string &name, const float value) const {
		glUniform1f(glGetUniformLocation(program, name.c_str()), value);
	}
	void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
		glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec2(const std::string &name, const float x, const float y) const {
		glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
	}
	void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
		glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec3(const std::string &name, const float x, const float y, const float z) const {
		glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
	}
	void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
		glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec4(const std::string &name, const float x, const float y, const float z, const float w) const {
		glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
	}
	void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
		glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
		glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
		glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	void Shader::use() {
		glUseProgram(program);
	}
}