#include "hello_imgui/hello_imgui.h"

#include "imgui_test_engine/imgui_te_engine.h"
#include "imgui_test_engine/imgui_te_context.h"
#include "imgui_test_engine/imgui_te_ui.h"


ImGuiTest *testOpenMetrics, *testCapture, *testExit;

void MyRegisterTests()
{
    ImGuiTestEngine* engine = HelloImGui::GetImGuiTestEngine();

    // ## Open Metrics window
    testOpenMetrics = IM_REGISTER_TEST(engine, "demo_tests", "open_metrics");
    testOpenMetrics->TestFunc = [](ImGuiTestContext* ctx)
    {
        ctx->SetRef("Dear ImGui Demo");
        ctx->MenuCheck("Tools/Metrics\\/Debugger");
    };

    // ## Capture entire Dear ImGui Demo window.
    testCapture= IM_REGISTER_TEST(engine, "demo_tests", "capture_screenshot");
    testCapture->TestFunc = [](ImGuiTestContext* ctx)
    {
        ctx->SetRef("Dear ImGui Demo");
        ctx->ItemOpen("Widgets");       // Open collapsing header
        ctx->ItemOpenAll("Basic");      // Open tree node and all its descendant
        ctx->CaptureScreenshotWindow("Dear ImGui Demo", ImGuiCaptureFlags_StitchAll | ImGuiCaptureFlags_HideMouseCursor);
    };


    testExit = IM_REGISTER_TEST(engine, "demo_tests", "exit");
    testExit->TestFunc = [](ImGuiTestContext* ctx)
    {
        ctx->ItemClick("**/Exit");
    };
}


void QueueAllTests()
{
    static int idxFrameCount = 0;
    ++idxFrameCount;
    if (idxFrameCount == 3)
    {
        auto engine = HelloImGui::GetImGuiTestEngine();

        ImGuiTestEngineIO& test_io = ImGuiTestEngine_GetIO(engine);
        test_io.ConfigRunSpeed = ImGuiTestRunSpeed_Fast;

        ImGuiTestEngine_QueueTest(engine, testOpenMetrics);
        ImGuiTestEngine_QueueTest(engine, testCapture);
        ImGuiTestEngine_QueueTest(engine, testExit);
    }
}


void AppGui()
{
    ImGui::Text("Hello");

    if (ImGui::Button("Exit"))
        HelloImGui::GetRunnerParams()->appShallExit = true;

    ImGui::ShowDemoWindow();
    ImGuiTestEngine_ShowTestEngineWindows(HelloImGui::GetImGuiTestEngine(), NULL);

    QueueAllTests();
}


int main(int, char *[])
{
    try
    {
        HelloImGui::RunnerParams runnerParams;
        runnerParams.useImGuiTestEngine = true;

        runnerParams.callbacks.ShowGui = AppGui;
        runnerParams.callbacks.RegisterTests = MyRegisterTests;
        HelloImGui::Run(runnerParams);
    }
    catch(...)
    {
        return 1;
    }
    return 0;
}
