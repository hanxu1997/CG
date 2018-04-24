<!DOCTYPE html>
<!-- saved from url=(0118)https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/basic_lighting_specular.cpp -->
<html lang="en"><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    
	<title>Code Viewer. Source code: src/2.lighting/2.2.basic_lighting_specular/basic_lighting_specular.cpp</title>
	<link rel="stylesheet" type="text/css" href="./lighting_2.2.basic_lighting_specular_basic_lighting_specular_files/layout.css">
    <link rel="stylesheet" type="text/css" href="./lighting_2.2.basic_lighting_specular_basic_lighting_specular_files/obsidian.css">
    <script src="./lighting_2.2.basic_lighting_specular_basic_lighting_specular_files/jquery-1.11.0.min.js.下载"></script>
    <script src="./lighting_2.2.basic_lighting_specular_basic_lighting_specular_files/hoverintent.js.下载"></script>
    <script src="./lighting_2.2.basic_lighting_specular_basic_lighting_specular_files/highlight.pack.js.下载"></script>
    <script src="./lighting_2.2.basic_lighting_specular_basic_lighting_specular_files/functions.js.下载"></script>
    <script type="text/javascript" src="./lighting_2.2.basic_lighting_specular_basic_lighting_specular_files/MathJax.js.下载"> // Has to be loaded last due to content bug </script>
    <script>hljs.initHighlightingOnLoad();</script>
    <script>
        window.onload = function() {
            $("#codez").mousedown(function() { switchNumbering(true); });
            $("#codez").mouseup(function() { switchNumbering(false); });
            
            function switchNumbering(hide)
            {     
                if(hide)
                    $('span.number').hide();
                else
                    $('span.number').show();
            }
            
            // Create all function callbacks
            SetFunctionTagCallbacks();
        };
        
    </script>
<style type="text/css">.MathJax_Hover_Frame {border-radius: .25em; -webkit-border-radius: .25em; -moz-border-radius: .25em; -khtml-border-radius: .25em; box-shadow: 0px 0px 15px #83A; -webkit-box-shadow: 0px 0px 15px #83A; -moz-box-shadow: 0px 0px 15px #83A; -khtml-box-shadow: 0px 0px 15px #83A; border: 1px solid #A6D ! important; display: inline-block; position: absolute}
.MathJax_Menu_Button .MathJax_Hover_Arrow {position: absolute; cursor: pointer; display: inline-block; border: 2px solid #AAA; border-radius: 4px; -webkit-border-radius: 4px; -moz-border-radius: 4px; -khtml-border-radius: 4px; font-family: 'Courier New',Courier; font-size: 9px; color: #F0F0F0}
.MathJax_Menu_Button .MathJax_Hover_Arrow span {display: block; background-color: #AAA; border: 1px solid; border-radius: 3px; line-height: 0; padding: 4px}
.MathJax_Hover_Arrow:hover {color: white!important; border: 2px solid #CCC!important}
.MathJax_Hover_Arrow:hover span {background-color: #CCC!important}
</style><style type="text/css">#MathJax_About {position: fixed; left: 50%; width: auto; text-align: center; border: 3px outset; padding: 1em 2em; background-color: #DDDDDD; color: black; cursor: default; font-family: message-box; font-size: 120%; font-style: normal; text-indent: 0; text-transform: none; line-height: normal; letter-spacing: normal; word-spacing: normal; word-wrap: normal; white-space: nowrap; float: none; z-index: 201; border-radius: 15px; -webkit-border-radius: 15px; -moz-border-radius: 15px; -khtml-border-radius: 15px; box-shadow: 0px 10px 20px #808080; -webkit-box-shadow: 0px 10px 20px #808080; -moz-box-shadow: 0px 10px 20px #808080; -khtml-box-shadow: 0px 10px 20px #808080; filter: progid:DXImageTransform.Microsoft.dropshadow(OffX=2, OffY=2, Color='gray', Positive='true')}
#MathJax_About.MathJax_MousePost {outline: none}
.MathJax_Menu {position: absolute; background-color: white; color: black; width: auto; padding: 2px; border: 1px solid #CCCCCC; margin: 0; cursor: default; font: menu; text-align: left; text-indent: 0; text-transform: none; line-height: normal; letter-spacing: normal; word-spacing: normal; word-wrap: normal; white-space: nowrap; float: none; z-index: 201; box-shadow: 0px 10px 20px #808080; -webkit-box-shadow: 0px 10px 20px #808080; -moz-box-shadow: 0px 10px 20px #808080; -khtml-box-shadow: 0px 10px 20px #808080; filter: progid:DXImageTransform.Microsoft.dropshadow(OffX=2, OffY=2, Color='gray', Positive='true')}
.MathJax_MenuItem {padding: 2px 2em; background: transparent}
.MathJax_MenuArrow {position: absolute; right: .5em; padding-top: .25em; color: #666666; font-size: .75em}
.MathJax_MenuActive .MathJax_MenuArrow {color: white}
.MathJax_MenuArrow.RTL {left: .5em; right: auto}
.MathJax_MenuCheck {position: absolute; left: .7em}
.MathJax_MenuCheck.RTL {right: .7em; left: auto}
.MathJax_MenuRadioCheck {position: absolute; left: 1em}
.MathJax_MenuRadioCheck.RTL {right: 1em; left: auto}
.MathJax_MenuLabel {padding: 2px 2em 4px 1.33em; font-style: italic}
.MathJax_MenuRule {border-top: 1px solid #CCCCCC; margin: 4px 1px 0px}
.MathJax_MenuDisabled {color: GrayText}
.MathJax_MenuActive {background-color: Highlight; color: HighlightText}
.MathJax_MenuDisabled:focus, .MathJax_MenuLabel:focus {background-color: #E8E8E8}
.MathJax_ContextMenu:focus {outline: none}
.MathJax_ContextMenu .MathJax_MenuItem:focus {outline: none}
#MathJax_AboutClose {top: .2em; right: .2em}
.MathJax_Menu .MathJax_MenuClose {top: -10px; left: -10px}
.MathJax_MenuClose {position: absolute; cursor: pointer; display: inline-block; border: 2px solid #AAA; border-radius: 18px; -webkit-border-radius: 18px; -moz-border-radius: 18px; -khtml-border-radius: 18px; font-family: 'Courier New',Courier; font-size: 24px; color: #F0F0F0}
.MathJax_MenuClose span {display: block; background-color: #AAA; border: 1.5px solid; border-radius: 18px; -webkit-border-radius: 18px; -moz-border-radius: 18px; -khtml-border-radius: 18px; line-height: 0; padding: 8px 0 6px}
.MathJax_MenuClose:hover {color: white!important; border: 2px solid #CCC!important}
.MathJax_MenuClose:hover span {background-color: #CCC!important}
.MathJax_MenuClose:hover:focus {outline: none}
</style><style type="text/css">.MathJax_Preview .MJXf-math {color: inherit!important}
</style><style type="text/css">.MJX_Assistive_MathML {position: absolute!important; top: 0; left: 0; clip: rect(1px, 1px, 1px, 1px); padding: 1px 0 0 0!important; border: 0!important; height: 1px!important; width: 1px!important; overflow: hidden!important; display: block!important; -webkit-touch-callout: none; -webkit-user-select: none; -khtml-user-select: none; -moz-user-select: none; -ms-user-select: none; user-select: none}
.MJX_Assistive_MathML.MJX_Assistive_MathML_Block {width: 100%!important}
</style><style type="text/css">#MathJax_Zoom {position: absolute; background-color: #F0F0F0; overflow: auto; display: block; z-index: 301; padding: .5em; border: 1px solid black; margin: 0; font-weight: normal; font-style: normal; text-align: left; text-indent: 0; text-transform: none; line-height: normal; letter-spacing: normal; word-spacing: normal; word-wrap: normal; white-space: nowrap; float: none; -webkit-box-sizing: content-box; -moz-box-sizing: content-box; box-sizing: content-box; box-shadow: 5px 5px 15px #AAAAAA; -webkit-box-shadow: 5px 5px 15px #AAAAAA; -moz-box-shadow: 5px 5px 15px #AAAAAA; -khtml-box-shadow: 5px 5px 15px #AAAAAA; filter: progid:DXImageTransform.Microsoft.dropshadow(OffX=2, OffY=2, Color='gray', Positive='true')}
#MathJax_ZoomOverlay {position: absolute; left: 0; top: 0; z-index: 300; display: inline-block; width: 100%; height: 100%; border: 0; padding: 0; margin: 0; background-color: white; opacity: 0; filter: alpha(opacity=0)}
#MathJax_ZoomFrame {position: relative; display: inline-block; height: 0; width: 0}
#MathJax_ZoomEventTrap {position: absolute; left: 0; top: 0; z-index: 302; display: inline-block; border: 0; padding: 0; margin: 0; background-color: white; opacity: 0; filter: alpha(opacity=0)}
</style><style type="text/css">.MathJax_Preview {color: #888}
#MathJax_Message {position: fixed; left: 1em; bottom: 1.5em; background-color: #E6E6E6; border: 1px solid #959595; margin: 0px; padding: 2px 8px; z-index: 102; color: black; font-size: 80%; width: auto; white-space: nowrap}
#MathJax_MSIE_Frame {position: absolute; top: 0; left: 0; width: 0px; z-index: 101; border: 0px; margin: 0px; padding: 0px}
.MathJax_Error {color: #CC0000; font-style: italic}
</style><style type="text/css">.MJXp-script {font-size: .8em}
.MJXp-right {-webkit-transform-origin: right; -moz-transform-origin: right; -ms-transform-origin: right; -o-transform-origin: right; transform-origin: right}
.MJXp-bold {font-weight: bold}
.MJXp-italic {font-style: italic}
.MJXp-scr {font-family: MathJax_Script,'Times New Roman',Times,STIXGeneral,serif}
.MJXp-frak {font-family: MathJax_Fraktur,'Times New Roman',Times,STIXGeneral,serif}
.MJXp-sf {font-family: MathJax_SansSerif,'Times New Roman',Times,STIXGeneral,serif}
.MJXp-cal {font-family: MathJax_Caligraphic,'Times New Roman',Times,STIXGeneral,serif}
.MJXp-mono {font-family: MathJax_Typewriter,'Times New Roman',Times,STIXGeneral,serif}
.MJXp-largeop {font-size: 150%}
.MJXp-largeop.MJXp-int {vertical-align: -.2em}
.MJXp-math {display: inline-block; line-height: 1.2; text-indent: 0; font-family: 'Times New Roman',Times,STIXGeneral,serif; white-space: nowrap; border-collapse: collapse}
.MJXp-display {display: block; text-align: center; margin: 1em 0}
.MJXp-math span {display: inline-block}
.MJXp-box {display: block!important; text-align: center}
.MJXp-box:after {content: " "}
.MJXp-rule {display: block!important; margin-top: .1em}
.MJXp-char {display: block!important}
.MJXp-mo {margin: 0 .15em}
.MJXp-mfrac {margin: 0 .125em; vertical-align: .25em}
.MJXp-denom {display: inline-table!important; width: 100%}
.MJXp-denom > * {display: table-row!important}
.MJXp-surd {vertical-align: top}
.MJXp-surd > * {display: block!important}
.MJXp-script-box > *  {display: table!important; height: 50%}
.MJXp-script-box > * > * {display: table-cell!important; vertical-align: top}
.MJXp-script-box > *:last-child > * {vertical-align: bottom}
.MJXp-script-box > * > * > * {display: block!important}
.MJXp-mphantom {visibility: hidden}
.MJXp-munderover {display: inline-table!important}
.MJXp-over {display: inline-block!important; text-align: center}
.MJXp-over > * {display: block!important}
.MJXp-munderover > * {display: table-row!important}
.MJXp-mtable {vertical-align: .25em; margin: 0 .125em}
.MJXp-mtable > * {display: inline-table!important; vertical-align: middle}
.MJXp-mtr {display: table-row!important}
.MJXp-mtd {display: table-cell!important; text-align: center; padding: .5em 0 0 .5em}
.MJXp-mtr > .MJXp-mtd:first-child {padding-left: 0}
.MJXp-mtr:first-child > .MJXp-mtd {padding-top: 0}
.MJXp-mlabeledtr {display: table-row!important}
.MJXp-mlabeledtr > .MJXp-mtd:first-child {padding-left: 0}
.MJXp-mlabeledtr:first-child > .MJXp-mtd {padding-top: 0}
.MJXp-merror {background-color: #FFFF88; color: #CC0000; border: 1px solid #CC0000; padding: 1px 3px; font-style: normal; font-size: 90%}
.MJXp-scale0 {-webkit-transform: scaleX(.0); -moz-transform: scaleX(.0); -ms-transform: scaleX(.0); -o-transform: scaleX(.0); transform: scaleX(.0)}
.MJXp-scale1 {-webkit-transform: scaleX(.1); -moz-transform: scaleX(.1); -ms-transform: scaleX(.1); -o-transform: scaleX(.1); transform: scaleX(.1)}
.MJXp-scale2 {-webkit-transform: scaleX(.2); -moz-transform: scaleX(.2); -ms-transform: scaleX(.2); -o-transform: scaleX(.2); transform: scaleX(.2)}
.MJXp-scale3 {-webkit-transform: scaleX(.3); -moz-transform: scaleX(.3); -ms-transform: scaleX(.3); -o-transform: scaleX(.3); transform: scaleX(.3)}
.MJXp-scale4 {-webkit-transform: scaleX(.4); -moz-transform: scaleX(.4); -ms-transform: scaleX(.4); -o-transform: scaleX(.4); transform: scaleX(.4)}
.MJXp-scale5 {-webkit-transform: scaleX(.5); -moz-transform: scaleX(.5); -ms-transform: scaleX(.5); -o-transform: scaleX(.5); transform: scaleX(.5)}
.MJXp-scale6 {-webkit-transform: scaleX(.6); -moz-transform: scaleX(.6); -ms-transform: scaleX(.6); -o-transform: scaleX(.6); transform: scaleX(.6)}
.MJXp-scale7 {-webkit-transform: scaleX(.7); -moz-transform: scaleX(.7); -ms-transform: scaleX(.7); -o-transform: scaleX(.7); transform: scaleX(.7)}
.MJXp-scale8 {-webkit-transform: scaleX(.8); -moz-transform: scaleX(.8); -ms-transform: scaleX(.8); -o-transform: scaleX(.8); transform: scaleX(.8)}
.MJXp-scale9 {-webkit-transform: scaleX(.9); -moz-transform: scaleX(.9); -ms-transform: scaleX(.9); -o-transform: scaleX(.9); transform: scaleX(.9)}
.MathJax_PHTML .noError {vertical-align: ; font-size: 90%; text-align: left; color: black; padding: 1px 3px; border: 1px solid}
</style></head>
<body style="margin: 0px; padding: 0px; background-image: none; background-color: rgb(40, 43, 46);" cz-shortcut-listen="true"><div id="MathJax_Message" style="display: none;"></div>

<pre style="width: 100%; height: 100%;"><code id="codez" style="margin:0; padding:25; border:0; border-radius:0;" class=" hljs cpp"><span class="hljs-preprocessor">#include &lt;glad/glad.h&gt;</span>
<span class="hljs-preprocessor">#include &lt;GLFW/glfw3.h&gt;</span>

<span class="hljs-preprocessor">#include &lt;glm/glm.hpp&gt;</span>
<span class="hljs-preprocessor">#include &lt;glm/gtc/matrix_transform.hpp&gt;</span>
<span class="hljs-preprocessor">#include &lt;glm/gtc/type_ptr.hpp&gt;</span>

<span class="hljs-preprocessor">#include &lt;</span><a href="https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h" target="_blank"><span class="hljs-preprocessor">learnopengl/shader_m.h</span></a><span class="hljs-preprocessor">&gt;</span>
<span class="hljs-preprocessor">#include &lt;</span><a href="https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h" target="_blank"><span class="hljs-preprocessor">learnopengl/camera.h</span></a><span class="hljs-preprocessor">&gt;</span>

<span class="hljs-preprocessor">#include &lt;iostream&gt;</span>

<span class="hljs-keyword">void</span> framebuffer_size_callback(GLFWwindow* window, <span class="hljs-keyword">int</span> width, <span class="hljs-keyword">int</span> height);
<span class="hljs-keyword">void</span> mouse_callback(GLFWwindow* window, <span class="hljs-keyword">double</span> xpos, <span class="hljs-keyword">double</span> ypos);
<span class="hljs-keyword">void</span> scroll_callback(GLFWwindow* window, <span class="hljs-keyword">double</span> xoffset, <span class="hljs-keyword">double</span> yoffset);
<span class="hljs-keyword">void</span> processInput(GLFWwindow *window);

<span class="hljs-comment">// settings</span>
<span class="hljs-keyword">const</span> <span class="hljs-keyword">unsigned</span> <span class="hljs-keyword">int</span> SCR_WIDTH = <span class="hljs-number">800</span>;
<span class="hljs-keyword">const</span> <span class="hljs-keyword">unsigned</span> <span class="hljs-keyword">int</span> SCR_HEIGHT = <span class="hljs-number">600</span>;

<span class="hljs-comment">// camera</span>
Camera camera(glm::<span class="hljs-built_in">vec3</span>(<span class="hljs-number">0.0f</span>, <span class="hljs-number">0.0f</span>, <span class="hljs-number">3.0f</span>));
<span class="hljs-keyword">float</span> lastX = SCR_WIDTH / <span class="hljs-number">2.0f</span>;
<span class="hljs-keyword">float</span> lastY = SCR_HEIGHT / <span class="hljs-number">2.0f</span>;
<span class="hljs-keyword">bool</span> firstMouse = <span class="hljs-keyword">true</span>;

<span class="hljs-comment">// timing</span>
<span class="hljs-keyword">float</span> deltaTime = <span class="hljs-number">0.0f</span>;	
<span class="hljs-keyword">float</span> lastFrame = <span class="hljs-number">0.0f</span>;

<span class="hljs-comment">// lighting</span>
glm::<span class="hljs-built_in">vec3</span> lightPos(<span class="hljs-number">1.2f</span>, <span class="hljs-number">1.0f</span>, <span class="hljs-number">2.0f</span>);

<span class="hljs-keyword">int</span> main()
{
    <span class="hljs-comment">// glfw: initialize and configure</span>
    <span class="hljs-comment">// ------------------------------</span>
   <function id="17"> glfwInit(</function>);
   <function id="18"> glfwWindowHint(</function>GLFW_CONTEXT_VERSION_MAJOR, <span class="hljs-number">3</span>);
   <function id="18"> glfwWindowHint(</function>GLFW_CONTEXT_VERSION_MINOR, <span class="hljs-number">3</span>);
   <function id="18"> glfwWindowHint(</function>GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

<span class="hljs-preprocessor">#ifdef __APPLE__</span>
   <function id="18"> glfwWindowHint(</function>GLFW_OPENGL_FORWARD_COMPAT, <span class="hljs-built_in">GL_TRUE</span>); <span class="hljs-comment">// uncomment this statement to fix compilation on OS X</span>
<span class="hljs-preprocessor">#endif</span>

    <span class="hljs-comment">// glfw window creation</span>
    <span class="hljs-comment">// --------------------</span>
    GLFWwindow* window =<function id="20"> glfwCreateWindow(</function>SCR_WIDTH, SCR_HEIGHT, <span class="hljs-string">"LearnOpenGL"</span>, NULL, NULL);
    <span class="hljs-keyword">if</span> (window == NULL)
    {
        <span class="hljs-built_in">std</span>::<span class="hljs-built_in">cout</span> &lt;&lt; <span class="hljs-string">"Failed to create GLFW window"</span> &lt;&lt; <span class="hljs-built_in">std</span>::<span class="hljs-built_in">endl</span>;
       <function id="25"> glfwTerminate(</function>);
        <span class="hljs-keyword">return</span> -<span class="hljs-number">1</span>;
    }
   <function id="19"> glfwMakeContextCurrent(</function>window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
   <function id="64"> glfwSetScrollCallback(</function>window, scroll_callback);

    <span class="hljs-comment">// tell GLFW to capture our mouse</span>
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    <span class="hljs-comment">// glad: load all OpenGL function pointers</span>
    <span class="hljs-comment">// ---------------------------------------</span>
    <span class="hljs-keyword">if</span> (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        <span class="hljs-built_in">std</span>::<span class="hljs-built_in">cout</span> &lt;&lt; <span class="hljs-string">"Failed to initialize GLAD"</span> &lt;&lt; <span class="hljs-built_in">std</span>::<span class="hljs-built_in">endl</span>;
        <span class="hljs-keyword">return</span> -<span class="hljs-number">1</span>;
    }

    <span class="hljs-comment">// configure global opengl state</span>
    <span class="hljs-comment">// -----------------------------</span>
   <function id="60"> glEnable(</function>GL_DEPTH_TEST);

    <span class="hljs-comment">// build and compile our shader zprogram</span>
    <span class="hljs-comment">// ------------------------------------</span>
    Shader lightingShader(<span class="hljs-string">"</span><a href="https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/2.2.basic_lighting.vs" target="_blank"><span class="hljs-string">2.2.basic_lighting.vs</span></a><span class="hljs-string">"</span>, <span class="hljs-string">"</span><a href="https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/2.2.basic_lighting.fs" target="_blank"><span class="hljs-string">2.2.basic_lighting.fs</span></a><span class="hljs-string">"</span>);
    Shader lampShader(<span class="hljs-string">"</span><a href="https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/2.2.lamp.vs" target="_blank"><span class="hljs-string">2.2.lamp.vs</span></a><span class="hljs-string">"</span>, <span class="hljs-string">"</span><a href="https://learnopengl.com/code_viewer_gh.php?code=src/2.lighting/2.2.basic_lighting_specular/2.2.lamp.fs" target="_blank"><span class="hljs-string">2.2.lamp.fs</span></a><span class="hljs-string">"</span>);

    <span class="hljs-comment">// set up vertex data (and buffer(s)) and configure vertex attributes</span>
    <span class="hljs-comment">// ------------------------------------------------------------------</span>
    <span class="hljs-keyword">float</span> vertices[] = {
        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,
         <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,
         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,
         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,
        -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,
        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,

        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,
         <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,
         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,
         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,
        -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,
        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,

        -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
        -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
        -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,

         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">0.0f</span>,

        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
        -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>, -<span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,

        -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
         <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
        -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>,
        -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.5f</span>, -<span class="hljs-number">0.5f</span>,  <span class="hljs-number">0.0f</span>,  <span class="hljs-number">1.0f</span>,  <span class="hljs-number">0.0f</span>
    };
    <span class="hljs-comment">// first, configure the cube's VAO (and VBO)</span>
    <span class="hljs-keyword">unsigned</span> <span class="hljs-keyword">int</span> VBO, cubeVAO;
   <function id="33"> glGenVertexArrays(</function><span class="hljs-number">1</span>, &amp;cubeVAO);
   <function id="12"> glGenBuffers(</function><span class="hljs-number">1</span>, &amp;VBO);

   <function id="32"> glBindBuffer(</function>GL_ARRAY_BUFFER, VBO);
   <function id="31"> glBufferData(</function>GL_ARRAY_BUFFER, <span class="hljs-keyword">sizeof</span>(vertices), vertices, GL_STATIC_DRAW);

   <function id="27"> glBindVertexArray(</function>cubeVAO);

    <span class="hljs-comment">// position attribute</span>
   <function id="30"> glVertexAttribPointer(</function><span class="hljs-number">0</span>, <span class="hljs-number">3</span>, <span class="hljs-built_in">GL_FLOAT</span>, <span class="hljs-built_in">GL_FALSE</span>, <span class="hljs-number">6</span> * <span class="hljs-keyword">sizeof</span>(<span class="hljs-keyword">float</span>), (<span class="hljs-keyword">void</span>*)<span class="hljs-number">0</span>);
   <function id="29"><function id="60"> glEnableV</function>ertexAttribArray(</function><span class="hljs-number">0</span>);
    <span class="hljs-comment">// normal attribute</span>
   <function id="30"> glVertexAttribPointer(</function><span class="hljs-number">1</span>, <span class="hljs-number">3</span>, <span class="hljs-built_in">GL_FLOAT</span>, <span class="hljs-built_in">GL_FALSE</span>, <span class="hljs-number">6</span> * <span class="hljs-keyword">sizeof</span>(<span class="hljs-keyword">float</span>), (<span class="hljs-keyword">void</span>*)(<span class="hljs-number">3</span> * <span class="hljs-keyword">sizeof</span>(<span class="hljs-keyword">float</span>)));
   <function id="29"><function id="60"> glEnableV</function>ertexAttribArray(</function><span class="hljs-number">1</span>);


    <span class="hljs-comment">// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)</span>
    <span class="hljs-keyword">unsigned</span> <span class="hljs-keyword">int</span> lightVAO;
   <function id="33"> glGenVertexArrays(</function><span class="hljs-number">1</span>, &amp;lightVAO);
   <function id="27"> glBindVertexArray(</function>lightVAO);

   <function id="32"> glBindBuffer(</function>GL_ARRAY_BUFFER, VBO);
    <span class="hljs-comment">// note that we update the lamp's position attribute's stride to reflect the updated buffer data</span>
   <function id="30"> glVertexAttribPointer(</function><span class="hljs-number">0</span>, <span class="hljs-number">3</span>, <span class="hljs-built_in">GL_FLOAT</span>, <span class="hljs-built_in">GL_FALSE</span>, <span class="hljs-number">6</span> * <span class="hljs-keyword">sizeof</span>(<span class="hljs-keyword">float</span>), (<span class="hljs-keyword">void</span>*)<span class="hljs-number">0</span>);
   <function id="29"><function id="60"> glEnableV</function>ertexAttribArray(</function><span class="hljs-number">0</span>);


    <span class="hljs-comment">// render loop</span>
    <span class="hljs-comment">// -----------</span>
    <span class="hljs-keyword">while</span> (<function id="14">!glfwWindowShouldClose(</function>window))
    {
        <span class="hljs-comment">// per-frame time logic</span>
        <span class="hljs-comment">// --------------------</span>
        <span class="hljs-keyword">float</span> currentFrame =<function id="47"> glfwGetTime(</function>);
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        <span class="hljs-comment">// input</span>
        <span class="hljs-comment">// -----</span>
        processInput(window);

        <span class="hljs-comment">// render</span>
        <span class="hljs-comment">// ------</span>
       <function id="13"><function id="10"> glClearC</function>olor(</function><span class="hljs-number">0.1f</span>, <span class="hljs-number">0.1f</span>, <span class="hljs-number">0.1f</span>, <span class="hljs-number">1.0f</span>);
       <function id="10"> glClear(</function>GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        <span class="hljs-comment">// be sure to activate shader when setting uniforms/drawing objects</span>
        lightingShader.use();
        lightingShader.setVec3(<span class="hljs-string">"objectColor"</span>, <span class="hljs-number">1.0f</span>, <span class="hljs-number">0.5f</span>, <span class="hljs-number">0.31f</span>);
        lightingShader.setVec3(<span class="hljs-string">"lightColor"</span>, <span class="hljs-number">1.0f</span>, <span class="hljs-number">1.0f</span>, <span class="hljs-number">1.0f</span>);
        lightingShader.setVec3(<span class="hljs-string">"lightPos"</span>, lightPos);
        lightingShader.setVec3(<span class="hljs-string">"viewPos"</span>, camera.Position);

        <span class="hljs-comment">// view/projection transformations</span>
        glm::<span class="hljs-built_in">mat4</span> projection = glm::perspective<function id="63">(glm::radians(</function>camera.Zoom), (<span class="hljs-keyword">float</span>)SCR_WIDTH / (<span class="hljs-keyword">float</span>)SCR_HEIGHT, <span class="hljs-number">0.1f</span>, <span class="hljs-number">100.0f</span>);
        glm::<span class="hljs-built_in">mat4</span> view = camera.GetViewMatrix();
        lightingShader.setMat4(<span class="hljs-string">"projection"</span>, projection);
        lightingShader.setMat4(<span class="hljs-string">"view"</span>, view);

        <span class="hljs-comment">// world transformation</span>
        glm::<span class="hljs-built_in">mat4</span> model;
        lightingShader.setMat4(<span class="hljs-string">"model"</span>, model);

        <span class="hljs-comment">// render the cube</span>
       <function id="27"> glBindVertexArray(</function>cubeVAO);
       <function id="1"> glDrawArrays(</function>GL_TRIANGLES, <span class="hljs-number">0</span>, <span class="hljs-number">36</span>);


        <span class="hljs-comment">// also draw the lamp object</span>
        lampShader.use();
        lampShader.setMat4(<span class="hljs-string">"projection"</span>, projection);
        lampShader.setMat4(<span class="hljs-string">"view"</span>, view);
        model = glm::<span class="hljs-built_in">mat4</span>();
        model =<function id="55"> glm::translate(</function>model, lightPos);
        model =<function id="56"> glm::scale(</function>model, glm::<span class="hljs-built_in">vec3</span>(<span class="hljs-number">0.2f</span>)); <span class="hljs-comment">// a smaller cube</span>
        lampShader.setMat4(<span class="hljs-string">"model"</span>, model);

       <function id="27"> glBindVertexArray(</function>lightVAO);
       <function id="1"> glDrawArrays(</function>GL_TRIANGLES, <span class="hljs-number">0</span>, <span class="hljs-number">36</span>);


        <span class="hljs-comment">// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)</span>
        <span class="hljs-comment">// -------------------------------------------------------------------------------</span>
       <function id="24"> glfwSwapBuffers(</function>window);
       <function id="23"> glfwPollEvents(</function>);
    }

    <span class="hljs-comment">// optional: de-allocate all resources once they've outlived their purpose:</span>
    <span class="hljs-comment">// ------------------------------------------------------------------------</span>
    glDeleteVertexArrays(<span class="hljs-number">1</span>, &amp;cubeVAO);
    glDeleteVertexArrays(<span class="hljs-number">1</span>, &amp;lightVAO);
    glDeleteBuffers(<span class="hljs-number">1</span>, &amp;VBO);

    <span class="hljs-comment">// glfw: terminate, clearing all previously allocated GLFW resources.</span>
    <span class="hljs-comment">// ------------------------------------------------------------------</span>
   <function id="25"> glfwTerminate(</function>);
    <span class="hljs-keyword">return</span> <span class="hljs-number">0</span>;
}

<span class="hljs-comment">// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly</span>
<span class="hljs-comment">// ---------------------------------------------------------------------------------------------------------</span>
<span class="hljs-keyword">void</span> processInput(GLFWwindow *window)
{
    <span class="hljs-keyword">if</span> (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, <span class="hljs-keyword">true</span>);

    <span class="hljs-keyword">if</span> (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    <span class="hljs-keyword">if</span> (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    <span class="hljs-keyword">if</span> (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    <span class="hljs-keyword">if</span> (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

<span class="hljs-comment">// glfw: whenever the window size changed (by OS or user resize) this callback function executes</span>
<span class="hljs-comment">// ---------------------------------------------------------------------------------------------</span>
<span class="hljs-keyword">void</span> framebuffer_size_callback(GLFWwindow* window, <span class="hljs-keyword">int</span> width, <span class="hljs-keyword">int</span> height)
{
    <span class="hljs-comment">// make sure the viewport matches the new window dimensions; note that width and </span>
    <span class="hljs-comment">// height will be significantly larger than specified on retina displays.</span>
   <function id="22"> glViewport(</function><span class="hljs-number">0</span>, <span class="hljs-number">0</span>, width, height);
}


<span class="hljs-comment">// glfw: whenever the mouse moves, this callback is called</span>
<span class="hljs-comment">// -------------------------------------------------------</span>
<span class="hljs-keyword">void</span> mouse_callback(GLFWwindow* window, <span class="hljs-keyword">double</span> xpos, <span class="hljs-keyword">double</span> ypos)
{
    <span class="hljs-keyword">if</span> (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = <span class="hljs-keyword">false</span>;
    }

    <span class="hljs-keyword">float</span> xoffset = xpos - lastX;
    <span class="hljs-keyword">float</span> yoffset = lastY - ypos; <span class="hljs-comment">// reversed since y-coordinates go from bottom to top</span>

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

<span class="hljs-comment">// glfw: whenever the mouse scroll wheel scrolls, this callback is called</span>
<span class="hljs-comment">// ----------------------------------------------------------------------</span>
<span class="hljs-keyword">void</span> scroll_callback(GLFWwindow* window, <span class="hljs-keyword">double</span> xoffset, <span class="hljs-keyword">double</span> yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}</code></pre>

<div id="hover" style="display: none; top: 691px; left: 136px;"><h2>glfwWindowHint</h2><h3>GLFW</h3><p></p><p>
  This function sets hints for the next call to <code>glfwCreateWindow</code>. The hints, once set, retain their values until changed by a another call to <code>glfwWindowHint</code>.
</p>

<p>
  The parameters of <code>glfwWindowHint(int target, int hint)</code> are as follows:
  </p><ul>
    <li><code>target</code>: sets the target/option that we want to change. Targets are set using one of GLFW's enums prefixed with <code>GLFW_</code>.</li>
    <li><code>hint</code>: the value/hint of the target that we want to set. </li>
  </ul>
<p></p>

<h4>Example usage</h4>
<pre class="cpp hljs "><code>
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, <span class="hljs-number">3</span>);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, <span class="hljs-number">3</span>);
glfwWindowHint(GLFW_RESIZABLE, <span class="hljs-built_in">GL_FALSE</span>);  
</code></pre><p></p></div>


</body></html>