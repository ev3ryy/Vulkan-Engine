#pragma once

#include "Window.h"
#include "Pipeline.h"
#include "Device.h"
#include "SwapChain.h"
#include "Model.h"

#include <memory>

namespace Engine {
	class Application {
	public:
		static constexpr int width = 800;
		static constexpr int height = 600;

		Application();
		~Application();

		Application(const Application&) = delete;
		Application& operator = (const Application&) = delete;

		void run();
	private:
		void sierpinski(std::vector<Model::Vertex>& vertices, int depth, glm::vec2 left, glm::vec2 right, glm::vec2 top);
		void loadModels();
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();
		void recreateSwapChain();
		void recordCommandbuffer(int imageIndex);

		Window MainWindow{ width, height, "Vulkan Engine" };
		Device device{ MainWindow };
		std::unique_ptr<SwapChain> swapChain;
		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		std::unique_ptr<Model> model;
	};
} // engine namespace