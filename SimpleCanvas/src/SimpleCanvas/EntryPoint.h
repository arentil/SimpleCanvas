#pragma once

extern sc::Application* sc::CreateApplication();

int main(int argc, char **argv)
{
	auto app = sc::CreateApplication();
	app->run();
	delete app;
}