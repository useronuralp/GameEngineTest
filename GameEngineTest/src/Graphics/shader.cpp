#include "pch.h"
#include "shader.h"
namespace GameEngineTest {
	namespace Graphics {	
		Shader::Shader(const char* vertPath, const char* fragPath)
		{	
			m_VertPath = vertPath;
			m_FragPath = fragPath;
			m_ShaderID = load();			
		}
		void Shader::enable() const
		{
			glUseProgram(m_ShaderID);
		}
		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}
		GLuint Shader::load()
		{		
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSourceString = FileUtils::read_file(m_VertPath);
			std::string fragSourceString = FileUtils::read_file(m_FragPath);

			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (!result) {
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if (!result) {
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glGetProgramiv(program, GL_LINK_STATUS, &result);
			if (!result) {
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to link shaders!" << std::endl << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}


		GLint Shader::getUniformLocation(const GLchar* name)
		{
			return glGetUniformLocation(m_ShaderID, name);
		}

		GLint Shader::getUniformLocation(std::string name)
		{
			char* arr;
			arr = &name[0];
			return glGetUniformLocation(m_ShaderID, arr);
		}

		void Shader::setUniform1f(const GLchar* name, const float value)
		{	
			enable();
			glUniform1f(getUniformLocation(name), value);
			disable();
		}
		void Shader::setUniform1fv(const GLchar* name, float* value ,int count)
		{	
			enable();
			glUniform1fv(getUniformLocation(name), count, value);
			disable();
		}
		void Shader::setUniform1i(const GLchar* name, const int value) 
		{	
			enable();
			glUniform1i(getUniformLocation(name), value);
			disable();
		}
		void Shader::setUniform1iv(const GLchar* name, int* value, int count)
		{	
			enable();
			glUniform1iv(getUniformLocation(name), count, value);
			disable();
		}
		void Shader::setUniform2f(const GLchar* name, const Math::vec2& vector) 
		{
			enable();
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
			disable();
		}
		void Shader::setUniform2f(const std::string name , const Math::vec2& vector)
		{
			enable();
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
			disable();
		}
		void Shader::setUniform3f(const GLchar* name, const Math::vec3& vector)
		{
			enable();
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
			disable();
		}
		void Shader::setUniform3f(const std::string name, const Math::vec3& vector)
		{
			enable();
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
			disable();
		}
		void Shader::setUniform4f(const GLchar* name, const Math::vec4& vector)
		{
			enable();
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w );
			disable();
		}
		void Shader::setUniformMat4(const GLchar* name, const Math::mat4& matrix)
		{
			enable();
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
			disable();
		}
	}
}