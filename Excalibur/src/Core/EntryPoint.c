#include "Application.h"

int main()
{
    Application* application = CreateApplication();
    RunApplication(application);
    DestroyApplication(application);
}
