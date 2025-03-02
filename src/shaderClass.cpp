#include "shaderClass.h"

std::string get_file_contents(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  std::cerr << "Error: Failed to open shader file " << filename << std::endl;
  return "";
}

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::string vertexCode = get_file_contents(vertexPath);
    std::string fragmentCode = get_file_contents(fragmentPath);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    compileErrors(vertexShader, "VERTEX");
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "FRAGMENT");
    
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    compileErrors(ID, "PROGRAM");
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
  glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type){
  GLint hasCompiled;
  char infolog[1024];
  if (type != "PROGRAM"){
    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE){
      glGetShaderInfoLog(shader, 1024, NULL, infolog);
      std::cout << "SHADER_COMPILATION_ERROR FOR :" << type << "\n" << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE){
      glGetProgramInfoLog(shader, 1024, NULL, infolog);
      std::cout << "SHADER_LINKING_ERROR FOR :" << type << "\n" << std::endl;
    }
  }
}