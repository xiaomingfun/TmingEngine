
//= INCLUDES ========================
#include "RHI_Shader.h"
#include "RHI_InputLayout.h"
//#include "spirv_hlsl.hpp"
#include "../3Part/SPIRV-Cross-2019-03-29/spirv_hlsl.hpp"
#include "../Core/Context.h"
#include "../Threading/Threading.h"
#include "../FileSystem/FileSystem.h"
//===================================

//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	RHI_Shader::RHI_Shader(const shared_ptr<RHI_Device>& rhi_device)
	{
		m_rhi_device	= rhi_device;
		m_input_layout	= make_shared<RHI_InputLayout>(rhi_device);
	}

	void RHI_Shader::Compile(const Shader_Type type, const string& shader, const RHI_Vertex_Attribute_Type vertex_attributes)
	{
		// Deduce name or file path
		if (FileSystem::IsDirectory(shader))
		{
			m_name.clear();
			m_file_path = shader;
		}
		else
		{
			m_name = FileSystem::GetFileNameFromFilePath(shader);
			m_file_path.clear();
		}

		// Compile
		if (type == Shader_Vertex)
		{
			m_compilation_state = Shader_Compiling;
			m_vertex_shader		= _Compile(type, shader, vertex_attributes);
			m_compilation_state = m_vertex_shader ? Shader_Compiled : Shader_Failed;
		}
		else if (type == Shader_Pixel)
		{
			m_compilation_state = Shader_Compiling;
			m_pixel_shader		= _Compile(type, shader);
			m_compilation_state = m_pixel_shader ? Shader_Compiled : Shader_Failed;
		}
		else if (type == Shader_VertexPixel)
		{
			m_compilation_state = Shader_Compiling;
			m_vertex_shader		= _Compile(Shader_Vertex, shader, vertex_attributes);
			m_pixel_shader		= _Compile(Shader_Pixel, shader);
			m_compilation_state = (m_vertex_shader && m_pixel_shader) ? Shader_Compiled : Shader_Failed;
		}

		// Log compilation result
		string shader_type = (type == Shader_Vertex) ? "vertex shader" : (type == Shader_Pixel) ? "pixel shader" : "vertex and pixel shader";
		if (m_compilation_state == Shader_Compiled)
		{
			LOGF_INFO("Successfully compiled %s from \"%s\"", shader_type.c_str(), shader.c_str());
		}
		else if (m_compilation_state == Shader_Failed)
		{
			LOGF_ERROR("Failed to compile %s from \"%s\"", shader_type.c_str(), shader.c_str());
		}
	}

	void RHI_Shader::CompileAsync(Context* context, const Shader_Type type, const string& shader, const RHI_Vertex_Attribute_Type vertex_attributes)
	{
		context->GetSubsystem<Threading>()->AddTask([this, type, shader, vertex_attributes]()
		{
			Compile(type, shader, vertex_attributes);
		});
	}

	void RHI_Shader::_Reflect(const Shader_Type type, const uint32_t* ptr, uint32_t size)
	{
		using namespace spirv_cross;

		// Initialize compiler with SPIR-V data
		auto compiler = CompilerHLSL(ptr, size);

		// The SPIR-V is now parsed, and we can perform reflection on it
		auto resources = compiler.get_shader_resources();

		// Get samplers
		for (const Resource& sampler : resources.separate_samplers)
		{
			uint32_t slot = compiler.get_decoration(sampler.id, spv::DecorationBinding);
			m_resources.emplace_back(sampler.name, RHI_Descriptor_Type::Descriptor_Sampler, slot, type);
		}

		// Get textures
		for (const Resource& image : resources.separate_images)
		{
			uint32_t slot = compiler.get_decoration(image.id, spv::DecorationBinding);
			m_resources.emplace_back(image.name, RHI_Descriptor_Type::Descriptor_Texture, slot, type);
		}

		// Get constant buffers
		for (const Resource& buffer : resources.uniform_buffers)
		{
			uint32_t slot = compiler.get_decoration(buffer.id, spv::DecorationBinding);
			m_resources.emplace_back(buffer.name, RHI_Descriptor_Type::Descriptor_ConstantBuffer, slot, type);
		}
	}
}
