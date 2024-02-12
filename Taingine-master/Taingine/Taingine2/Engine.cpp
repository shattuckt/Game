#include "Engine.h"

Engine::Engine(Window* window, Mouse* mouse, Keyboard* keyboard, Timer* timer, StateManager* stateManager) {
	this->window = window;
	this->mouse = mouse;
	this->keyboard = keyboard;
	this->timer = timer;
	this->stateManager = stateManager;
}

Engine* Engine::init(EngineConfigs configs) {
	initResFolder();
	//ErrorManager.init //I dont know if I want this tbh
	//GameText.init(EngineFiles.LANG_FILE, configs.languageID); //do this later
	//BackgroundLoader.init(); //do this too?
	Window* window = setUpWindow(configs);
	Keyboard* keyboard = new Keyboard(window->getId());
	Mouse* mouse = new Mouse(window);
	Timer* timer = new Timer(window->getFps());
	//initOpenGl(window->getPixelWidth(), window->getPixelHeight());
	//initUiMaster(window, mouse, configs.windowMinWidth, configs.windowMinHeight, configs.UiSize);
	StateManager* stateManager = new StateManager(configs.defaultState, configs.initialState);
	return new Engine(window, mouse, keyboard, timer, stateManager);
}
Window* Engine::getWindow() {
	return this->window;
}
Keyboard* Engine::getKeyboard() {
	return this->keyboard;
}
Mouse* Engine::getMouse() {
	return this->mouse;
}
StateManager* Engine::getStateManager() {
	return this->stateManager;
}
float Engine::getDeltaSeconds() {
	return timer->getDelta();
}
void Engine::update() {
	//UiMaster.update(timer->getDelta());
	//BackgroundLoader.update();
	keyboard->update();
	mouse->update();
	window->update();
	timer->update();
	stateManager->updateState();
}
void Engine::cleanUp() {
	//BackgroundLoder.cleanUp();
	//UiMaster.cleanUp();
	window->destroy();
}
void Engine::requestClose() {
	this->closeFlag = true;
}
bool Engine::isCloseRequested() {
	return closeFlag || window->closeButtonPressed();
}

void Engine::initOpenGl(int pixelWidth, int pixelHeight) {
	glViewport(0, 0, pixelWidth, pixelHeight);
}
Window* Engine::setUpWindow(EngineConfigs configs) {
	std::vector<GLFWimage> image = loadWindowIcon();
	Window* window = Window::newWindow(configs.windowWidth, configs.windowHeight, configs.windowTitle)
		->setVsync(configs.vsync)->fullscreen(configs.fullscreen)->withIcon(image)->setMSAA(configs.msaa)
		->setFps(configs.fps)->create();
	return window;
}
void Engine::initUiMaster(Window* window, Mouse* mouse, int minWidth, int minHeight, float uiSize) {
	//UiMaster.init(mouse, window.getPixelWidth(), window.getPixelHeight(), uiSize);
	//UiMaster.setMinDisplaySize(minWidth, minHeight);
	//window.addSizeChangeListener((width, height) -> UiMaster.notifyScreenSizeChange(width, height));
}
void Engine::initResFolder() {
	if (!EngineFiles::RES_FOLDER.empty()) {
		return;
	}
	//_FILESYSTEM_::create_   make directories dynamically? not sure how that is good practice. 
}
std::vector<GLFWimage> Engine::loadWindowIcon() {
	std::vector<std::string> filePaths;
	if (!EngineFiles::ICON_FOLDER.empty()) {
		for (const auto& file : std::filesystem::directory_iterator(EngineFiles::ICON_FOLDER)) {
			std::filesystem::path path{ file };
			std::string path_string{ path.u8string() };
			filePaths.push_back(path_string);
		}
	}
	return IconLoader::loadIcon(filePaths);

}