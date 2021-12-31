#include <ShaderManager.h>

ShaderProgram* ShaderManager::getShader(std::string shadername) {
    for (ShaderProgram& sp : shaders) {
        if (sp.getName() == shadername) {
            return &sp;
        }
    }
    return nullptr;
}

void ShaderManager::load_shader(std::string shadername) {
    // check if already loaded
    if (getShader(shadername) != nullptr) return;
    ShaderProgram sp;
    sp.load(ShaderProgram::get_shader_file("vertex\\" + shadername + ".vs").c_str(),
            ShaderProgram::get_shader_file("fragment\\" + shadername + ".fs").c_str());

    // WARNING: cannot have dynamically allocated members on Shader Program.
    if (sp.isLoaded()) {
        sp.setName(shadername);
        this->shaders.push_back(sp);
        }
}

ShaderManager::ShaderManager() {
}