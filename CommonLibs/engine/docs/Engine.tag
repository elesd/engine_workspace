<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>SlotHolder.h</name>
    <path>E:/Programing/Projects/EngineWorkspace/CommonLibs/engine/include/engine/signalSlot/</path>
    <filename>a00141</filename>
    <class kind="class">engine::SlotHolder</class>
  </compound>
  <compound kind="class">
    <name>engine::Application</name>
    <filename>a00002.html</filename>
    <base protection="private">engine::NonCopyable</base>
    <member kind="function">
      <type></type>
      <name>Application</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a8ba1a5c0ffacfa8c22797d62722f1359</anchor>
      <arglist>(std::unique_ptr&lt; IApplicationParameter &gt; arguments, std::unique_ptr&lt; IMain &gt; main)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Application</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a02c92008318072312a4f972298c77246</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a149822f20163e98d41728f4752d7a7f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>render</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>af3ef70b1c3e25be0dbe68c460ec2db98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isActive</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a86f249cf621c4255df1a60987c588961</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>aeb61beceae055e7681b6791dd5dddafa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>start</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a9b8b10fd48e93db0986df610523105dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const IApplicationParameter *</type>
      <name>getArguments</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>af165b483b86469ff9db2f689f1212f14</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::ApplicationBuilder</name>
    <filename>a00003.html</filename>
    <base>engine::BaseBuilder</base>
    <member kind="function">
      <type>EventBuilder</type>
      <name>build</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a7ca2bdeae296ff836f6592b66d819e87</anchor>
      <arglist>(std::unique_ptr&lt; IApplicationParameter &gt; arguments, std::unique_ptr&lt; IMain &gt; main)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>addModule</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52fb449fadc5d3a074e3fc7bfb56744b</anchor>
      <arglist>(const ContextModuleType value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setApplication</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a20c5dafa6892142bc352c13a5f3ac09a</anchor>
      <arglist>(std::unique_ptr&lt; Application &gt; app)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setWindowManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a641fb06484bdb07220f445f14db8c0e7</anchor>
      <arglist>(std::unique_ptr&lt; WindowManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setEventManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52b490a3ef4d2a5b5b7e8e0f82d9a27c</anchor>
      <arglist>(std::unique_ptr&lt; EventManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setInitialized</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>af23e3bdfb30ca9f2076cacc9029d96c2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::winapi::ApplicationImpl</name>
    <filename>a00004.html</filename>
    <base>engine::Application</base>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a149822f20163e98d41728f4752d7a7f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>render</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>af3ef70b1c3e25be0dbe68c460ec2db98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isActive</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a86f249cf621c4255df1a60987c588961</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>aeb61beceae055e7681b6791dd5dddafa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>start</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a9b8b10fd48e93db0986df610523105dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const IApplicationParameter *</type>
      <name>getArguments</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>af165b483b86469ff9db2f689f1212f14</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::BaseBuilder</name>
    <filename>a00005.html</filename>
    <base protection="private">engine::NonCopyable</base>
    <member kind="function" protection="protected">
      <type></type>
      <name>BaseBuilder</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>ac1d22d4031be98e715d8ea733fc4463b</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~BaseBuilder</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>af762f3acae53396e0621113e1bb3156b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>addModule</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52fb449fadc5d3a074e3fc7bfb56744b</anchor>
      <arglist>(const ContextModuleType value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setApplication</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a20c5dafa6892142bc352c13a5f3ac09a</anchor>
      <arglist>(std::unique_ptr&lt; Application &gt; app)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setWindowManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a641fb06484bdb07220f445f14db8c0e7</anchor>
      <arglist>(std::unique_ptr&lt; WindowManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setEventManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52b490a3ef4d2a5b5b7e8e0f82d9a27c</anchor>
      <arglist>(std::unique_ptr&lt; EventManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setInitialized</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>af23e3bdfb30ca9f2076cacc9029d96c2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::test::BaseRegression</name>
    <filename>a00006.html</filename>
    <base protection="private">engine::NonCopyable</base>
  </compound>
  <compound kind="struct">
    <name>engine::BufferDesc</name>
    <filename>a00007.html</filename>
    <member kind="variable">
      <type>TextureFormat</type>
      <name>format</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>a5a84b0faa10bdbcd51ddb3936295d82c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BufferType</type>
      <name>type</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>aaac2389a71fd61b51cd539da66fbc240</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>isSRGB</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>a50a45012458646eb58890de16c6f5fae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>BufferFormat</type>
      <name>format</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>a99d4db16d6b3d3bbb5da5ac64610bb3a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::glfw::BufferDescUtils</name>
    <filename>a00008.html</filename>
    <class kind="struct">engine::glfw::BufferDescUtils::GlfwDesc</class>
  </compound>
  <compound kind="struct">
    <name>engine::sdl::BufferDescUtils</name>
    <filename>a00009.html</filename>
  </compound>
  <compound kind="struct">
    <name>engine::winapi::BufferDescUtils</name>
    <filename>a00010.html</filename>
    <member kind="function" static="yes">
      <type>static DXGI_FORMAT</type>
      <name>EncodeDesc</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>ad419c2a5742a873e18a0bf3ba9d50b87</anchor>
      <arglist>(const BufferDesc &amp;desc)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::BuildFinalizer</name>
    <filename>a00011.html</filename>
    <base>engine::BaseBuilder</base>
    <member kind="function">
      <type></type>
      <name>BuildFinalizer</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>abb814b037e8526d18118036c5142c96a</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>BuildFinalizer</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>ac23ed21d3f95a3c91ecdf900387fd9c6</anchor>
      <arglist>(BuildFinalizer &amp;&amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>build</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a1a1fa8cbc1658b9a0240845c9335ab47</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>addModule</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52fb449fadc5d3a074e3fc7bfb56744b</anchor>
      <arglist>(const ContextModuleType value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setApplication</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a20c5dafa6892142bc352c13a5f3ac09a</anchor>
      <arglist>(std::unique_ptr&lt; Application &gt; app)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setWindowManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a641fb06484bdb07220f445f14db8c0e7</anchor>
      <arglist>(std::unique_ptr&lt; WindowManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setEventManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52b490a3ef4d2a5b5b7e8e0f82d9a27c</anchor>
      <arglist>(std::unique_ptr&lt; EventManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setInitialized</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>af23e3bdfb30ca9f2076cacc9029d96c2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::Context</name>
    <filename>a00012.html</filename>
    <base>Singleton&lt; Context &gt;</base>
    <member kind="function">
      <type>Application *</type>
      <name>getApplication</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a6f657b971312b31eab5ff0b2148fab05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Context *</type>
      <name>getInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a90ed1f21b1811a569eafccc78fcd12ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>createInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a571e434c8ff771bf65de40f8a7b22076</anchor>
      <arglist>(Args...args)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>releaseInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a3fbed1f6a78cdf1d0c11467a3be61841</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>ac532ff9bb55da7d1c351f1c2a0064f6d</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::ContextBuilder</name>
    <filename>a00013.html</filename>
    <base>engine::BaseBuilder</base>
    <member kind="function">
      <type></type>
      <name>ContextBuilder</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>aca8c1a2731d9f2da0d0cb3fa150c314c</anchor>
      <arglist>(const std::vector&lt; ContextModuleType &gt; &amp;moduls)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ContextBuilder</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>ae8a046bccdc9e1461de3f952e15df0e4</anchor>
      <arglist>(ContextBuilder &amp;&amp;o)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ContextBuilder</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>acbc8b557d2a1755b41dc4e39cfefaa79</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ApplicationBuilder</type>
      <name>buildForApplication</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a397a774fc36c66dda2ee90a56f4094e1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>addModule</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52fb449fadc5d3a074e3fc7bfb56744b</anchor>
      <arglist>(const ContextModuleType value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setApplication</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a20c5dafa6892142bc352c13a5f3ac09a</anchor>
      <arglist>(std::unique_ptr&lt; Application &gt; app)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setWindowManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a641fb06484bdb07220f445f14db8c0e7</anchor>
      <arglist>(std::unique_ptr&lt; WindowManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setEventManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52b490a3ef4d2a5b5b7e8e0f82d9a27c</anchor>
      <arglist>(std::unique_ptr&lt; EventManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setInitialized</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>af23e3bdfb30ca9f2076cacc9029d96c2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::ContextModule_traits</name>
    <filename>a00014.html</filename>
    <templarg>type</templarg>
  </compound>
  <compound kind="struct">
    <name>engine::ContextModule_traits&lt; ContextModuleType::Glfw &gt;</name>
    <filename>a00015.html</filename>
  </compound>
  <compound kind="struct">
    <name>engine::ContextModule_traits&lt; ContextModuleType::Sdl &gt;</name>
    <filename>a00016.html</filename>
  </compound>
  <compound kind="struct">
    <name>engine::ContextModule_traits&lt; ContextModuleType::WinApi &gt;</name>
    <filename>a00017.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::glfw::Core</name>
    <filename>a00018.html</filename>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>init</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a54bfba36517cae500798aae57ce31c12</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::sdl::Core</name>
    <filename>a00019.html</filename>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>init</name>
      <anchorfile>a00019.html</anchorfile>
      <anchor>a19e45cac77785c72dfb09888d65d4bcc</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::winapi::Core</name>
    <filename>a00020.html</filename>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>init</name>
      <anchorfile>a00020.html</anchorfile>
      <anchor>a908c19ff86e54cf37ddcddeb55e610ae</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::CountedObject</name>
    <filename>a00021.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static uint64_t</type>
      <name>getObjectCount</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>a693c549c84cd89d45e46018f9d2f1420</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>CountedObject</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>a9f4f5b1610e616b8c7ffa347c99729e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~CountedObject</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>a8858bb0d52059b19ffa684c7dc716fe3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::CustomPlaceholder</name>
    <filename>a00022.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="struct">
    <name>engine::DeclTypeToType</name>
    <filename>a00023.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>engine::Driver</name>
    <filename>a00024.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Driver</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4772e871ef5639c84cbb5569d75c1de9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4e283b1274b6ffea595cb7329b09c16d</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Driver</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4772e871ef5639c84cbb5569d75c1de9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4e283b1274b6ffea595cb7329b09c16d</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>Driver</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>aed71bf52de93e2fc50f12eb860a52acc</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>Driver</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>aed71bf52de93e2fc50f12eb860a52acc</anchor>
      <arglist>()=default</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::glfw::DriverImpl</name>
    <filename>a00025.html</filename>
    <base>engine::Driver</base>
    <member kind="function">
      <type></type>
      <name>DriverImpl</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>a97b0fadb208251c7a998e0a1e2480a67</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DriverImpl</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>a18a74e07839478fede104c56a7ec73a1</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initImpl</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>ab25927deeb820162e36fe494e6abb357</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4e283b1274b6ffea595cb7329b09c16d</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4e283b1274b6ffea595cb7329b09c16d</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::sdl::DriverImpl</name>
    <filename>a00026.html</filename>
    <base>engine::Driver</base>
    <member kind="function">
      <type></type>
      <name>DriverImpl</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a0a1b946eea9e2d648d98be26caeb2c60</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DriverImpl</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>afc245b5c1c99e8b5d73e14c52239e319</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initImpl</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a831cf6d2ef096f515727d23f19ab9d41</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4e283b1274b6ffea595cb7329b09c16d</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4e283b1274b6ffea595cb7329b09c16d</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::winapi::DriverImpl</name>
    <filename>a00027.html</filename>
    <base>engine::Driver</base>
    <member kind="function">
      <type></type>
      <name>DriverImpl</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>a5819d40195dd4ecc23de16090c20f746</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DriverImpl</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>a700cf49e15416ea10fc567459535f9f1</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initImpl</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>a1a6bbae98bc32e3c78c0a47092bda76a</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4e283b1274b6ffea595cb7329b09c16d</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a4e283b1274b6ffea595cb7329b09c16d</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *window)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::DriverInitParameters</name>
    <filename>a00028.html</filename>
    <member kind="variable">
      <type>BufferDesc</type>
      <name>description</name>
      <anchorfile>a00028.html</anchorfile>
      <anchor>a3c2e3a43440396f00417f098628c6649</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int32_t</type>
      <name>sampleCount</name>
      <anchorfile>a00028.html</anchorfile>
      <anchor>afab1afded563f9ab42273f7993cdf3ed</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::EasyBuilder</name>
    <filename>a00029.html</filename>
    <base protection="private">engine::NonCopyable</base>
    <base protection="private">engine::NonMoveable</base>
  </compound>
  <compound kind="struct">
    <name>engine::EqualTo</name>
    <filename>a00030.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>EqualTo</name>
      <anchorfile>a00030.html</anchorfile>
      <anchor>a6f4b19b5863bd40d6c3e424728e5e840</anchor>
      <arglist>(const T &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00030.html</anchorfile>
      <anchor>a647e825983c17aac5428bd7f2847c7da</anchor>
      <arglist>(const T &amp;o)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::EventBuilder</name>
    <filename>a00031.html</filename>
    <base>engine::BaseBuilder</base>
    <member kind="enumeration">
      <type></type>
      <name>BasicInputType</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>a6d136f2bc5e63ae4dc52882adcb48ab1</anchor>
      <arglist></arglist>
      <enumvalue file="a00031.html" anchor="a6d136f2bc5e63ae4dc52882adcb48ab1af2a47c6809d88e175dade0ef7b16aa13">Mouse</enumvalue>
      <enumvalue file="a00031.html" anchor="a6d136f2bc5e63ae4dc52882adcb48ab1a6ce4d85a628a88bbdb3ac24a8e5a9c2e">Keyboard</enumvalue>
    </member>
    <member kind="function">
      <type></type>
      <name>EventBuilder</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>aa0d7040cb93143af643873f0b8999120</anchor>
      <arglist>(EventBuilder &amp;&amp;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~EventBuilder</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>ad8bbbc8c0cb10337a73cde239a44be2e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>WindowEnvironmentBuilder</type>
      <name>build</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>af77f14d7c5ff0be93dda1520f3441096</anchor>
      <arglist>(const std::set&lt; BasicInputType &gt; &amp;basicInputs)</arglist>
    </member>
    <member kind="function">
      <type>WindowEnvironmentBuilder</type>
      <name>skip</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>a0c6c7712c1057dcb7e07a5aecfca5841</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>addModule</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52fb449fadc5d3a074e3fc7bfb56744b</anchor>
      <arglist>(const ContextModuleType value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setApplication</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a20c5dafa6892142bc352c13a5f3ac09a</anchor>
      <arglist>(std::unique_ptr&lt; Application &gt; app)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setWindowManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a641fb06484bdb07220f445f14db8c0e7</anchor>
      <arglist>(std::unique_ptr&lt; WindowManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setEventManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52b490a3ef4d2a5b5b7e8e0f82d9a27c</anchor>
      <arglist>(std::unique_ptr&lt; EventManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setInitialized</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>af23e3bdfb30ca9f2076cacc9029d96c2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::EventContainer</name>
    <filename>a00032.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::EventHandler</name>
    <filename>a00033.html</filename>
    <base>engine::EventSourceBase</base>
    <base protection="private">engine::EventContainer</base>
  </compound>
  <compound kind="class">
    <name>engine::EventManager</name>
    <filename>a00034.html</filename>
    <base protection="private">engine::NonCopyable</base>
    <base protection="private">engine::NonMoveable</base>
  </compound>
  <compound kind="class">
    <name>engine::winapi::EventManagerImpl</name>
    <filename>a00035.html</filename>
    <base>engine::EventManager</base>
  </compound>
  <compound kind="class">
    <name>engine::EventSourceBase</name>
    <filename>a00036.html</filename>
    <base>PIMPLCopyable&lt; EventSourceBase &gt;</base>
    <base>PIMPLMoveable&lt; EventSourceBase &gt;</base>
  </compound>
  <compound kind="struct">
    <name>engine::ExpiredError</name>
    <filename>a00037.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::Game</name>
    <filename>a00038.html</filename>
    <base>engine::Application</base>
    <member kind="function">
      <type></type>
      <name>Game</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a9b20c295fd6af60e00709da9ff9cde89</anchor>
      <arglist>(std::unique_ptr&lt; IApplicationParameter &gt; arguments, std::unique_ptr&lt; IMain &gt; main)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Game</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a36ee1fe045159234e2916e20f0d94562</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setStartState</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a395e9435f60c020fb7687f23e4ebca3a</anchor>
      <arglist>(std::unique_ptr&lt; engine::StateBase &gt; startState)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a149822f20163e98d41728f4752d7a7f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>render</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>af3ef70b1c3e25be0dbe68c460ec2db98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isActive</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a86f249cf621c4255df1a60987c588961</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>aeb61beceae055e7681b6791dd5dddafa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>start</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a9b8b10fd48e93db0986df610523105dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const IApplicationParameter *</type>
      <name>getArguments</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>af165b483b86469ff9db2f689f1212f14</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::test::GameAssertException</name>
    <filename>a00039.html</filename>
  </compound>
  <compound kind="struct">
    <name>engine::GenSequence</name>
    <filename>a00040.html</filename>
    <templarg>N</templarg>
    <templarg>Is</templarg>
  </compound>
  <compound kind="struct">
    <name>engine::GenSequence&lt; 0, Is... &gt;</name>
    <filename>a00041.html</filename>
    <templarg>Is</templarg>
    <base>Index&lt; Is... &gt;</base>
  </compound>
  <compound kind="struct">
    <name>engine::glfw::BufferDescUtils::GlfwDesc</name>
    <filename>a00042.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::IApplicationParameter</name>
    <filename>a00043.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::IdGenerator</name>
    <filename>a00044.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static uint32_t</type>
      <name>generateNextId</name>
      <anchorfile>a00044.html</anchorfile>
      <anchor>a211645f2f83332a1fb76671cfffd638c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::IMain</name>
    <filename>a00045.html</filename>
    <base protection="private">engine::NonCopyable</base>
    <member kind="function">
      <type></type>
      <name>~IMain</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a3e512e4387b1517f99466e1eb01e0d78</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>load</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>aaddfdf70642e7bd6df3256e7074fa571</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>update</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a6ae095ca594d7ad67704efc97bb50adf</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>render</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>abf626b47003850fbfb5fc334409c80ec</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>IMain</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a7123c5ea514a788ba01089f3a257b72b</anchor>
      <arglist>()=default</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::IModuleExtension</name>
    <filename>a00046.html</filename>
  </compound>
  <compound kind="struct">
    <name>engine::Index</name>
    <filename>a00047.html</filename>
    <templarg>Is</templarg>
  </compound>
  <compound kind="class">
    <name>Index&lt; Is... &gt;</name>
    <filename>a00047.html</filename>
  </compound>
  <compound kind="struct">
    <name>engine::InitializationError</name>
    <filename>a00048.html</filename>
    <member kind="function">
      <type></type>
      <name>InitializationError</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a7292c661ed6737cf6a041176398e9893</anchor>
      <arglist>(const std::string &amp;error)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>InitializationError</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a4313a4d837f17721d89740f940042eb2</anchor>
      <arglist>(const char *error)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>std::is_placeholder&lt; engine::CustomPlaceholder&lt; N &gt; &gt;</name>
    <filename>a00049.html</filename>
    <templarg>N</templarg>
  </compound>
  <compound kind="class">
    <name>engine::ISignal</name>
    <filename>a00050.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::ISignalManager</name>
    <filename>a00051.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ISignalManager</name>
      <anchorfile>a00051.html</anchorfile>
      <anchor>a96df44c1e1235d42d5632a5138d684e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>addTask</name>
      <anchorfile>a00051.html</anchorfile>
      <anchor>a45dd8b6dff3657f3538946bf1a8ea77c</anchor>
      <arglist>(std::unique_ptr&lt; ISignalTask &gt; task)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>update</name>
      <anchorfile>a00051.html</anchorfile>
      <anchor>ab28b704d755b789e6f88d7c30e2aa625</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>ISignalManager</name>
      <anchorfile>a00051.html</anchorfile>
      <anchor>a2ff4db6b18c05b22db35c9d62bed82bc</anchor>
      <arglist>()=default</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::ISignalTask</name>
    <filename>a00052.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ISignalTask</name>
      <anchorfile>a00052.html</anchorfile>
      <anchor>a8f7c6610cc8bfd5249d3b391c6efc95b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>operator()</name>
      <anchorfile>a00052.html</anchorfile>
      <anchor>ab7e5dedd50f908fdb0f203b0a154db54</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>isExpired</name>
      <anchorfile>a00052.html</anchorfile>
      <anchor>aaa397480f1ad28755a63ad1dca559d50</anchor>
      <arglist>() const  =0</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::ItemNotFound</name>
    <filename>a00053.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::test::ITestCase</name>
    <filename>a00054.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::Keyboard</name>
    <filename>a00055.html</filename>
    <base>engine::EventSourceBase</base>
    <base>engine::SlotHolder</base>
    <member kind="function">
      <type></type>
      <name>Keyboard</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>ac81d08f53f7b2b4917dfb2785529651b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Keyboard</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>abc61f7323ef7912d9de86e831ae09725</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Keyboard</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>ad4410c745ee235f4418feb55656f59e2</anchor>
      <arglist>(Keyboard &amp;&amp;o)</arglist>
    </member>
    <member kind="function">
      <type>Keyboard &amp;</type>
      <name>operator=</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>acbdb16f8b16fe00da53eab07736f6364</anchor>
      <arglist>(Keyboard &amp;&amp;o)</arglist>
    </member>
    <member kind="function">
      <type>KeyState</type>
      <name>getKeyState</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>abdc913f90b83dca91c497f811d00602a</anchor>
      <arglist>(KeyboardButton) const </arglist>
    </member>
    <member kind="function">
      <type>ISignalManager *</type>
      <name>getSignalManager</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a324f41177f75c6d08ad6494c36a65806</anchor>
      <arglist>() const  override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assignSignal</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>afd9ce54a72b4dd397d82aff6c387d0c0</anchor>
      <arglist>(ISignal *signal)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeSignal</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>a5927b57f0d4fb8744dc0e8ec265e0136</anchor>
      <arglist>(ISignal *signal)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>KeyboardButtonToString</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>ae9afce424611d4405266ce4ecfbac6a3</anchor>
      <arglist>(KeyboardButton)</arglist>
    </member>
    <member kind="variable">
      <type>Signal&lt; KeyboardButton &gt;</type>
      <name>keyPressed</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a96ef16f70810ff3ceffde1ad71f9291f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Signal&lt; KeyboardButton &gt;</type>
      <name>keyReleased</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a081464fd7756415ad9c78e80e850cbea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>EventSourceId</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a11ae52b8b6e7519d0b3ea42561d6dccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>onKeyPressed</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a5072ad733814bd17d46e36ea8be4a4b4</anchor>
      <arglist>(KeyboardButton)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>onKeyReleased</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a000acdad189778380e4ac141dd4619cb</anchor>
      <arglist>(KeyboardButton)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::winapi::KeyboardImpl</name>
    <filename>a00056.html</filename>
    <base>engine::Keyboard</base>
    <member kind="function">
      <type>KeyState</type>
      <name>getKeyState</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>abdc913f90b83dca91c497f811d00602a</anchor>
      <arglist>(KeyboardButton) const </arglist>
    </member>
    <member kind="function">
      <type>ISignalManager *</type>
      <name>getSignalManager</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a324f41177f75c6d08ad6494c36a65806</anchor>
      <arglist>() const  override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assignSignal</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>afd9ce54a72b4dd397d82aff6c387d0c0</anchor>
      <arglist>(ISignal *signal)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeSignal</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>a5927b57f0d4fb8744dc0e8ec265e0136</anchor>
      <arglist>(ISignal *signal)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>KeyboardButtonToString</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>ae9afce424611d4405266ce4ecfbac6a3</anchor>
      <arglist>(KeyboardButton)</arglist>
    </member>
    <member kind="variable">
      <type>Signal&lt; KeyboardButton &gt;</type>
      <name>keyPressed</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a96ef16f70810ff3ceffde1ad71f9291f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Signal&lt; KeyboardButton &gt;</type>
      <name>keyReleased</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a081464fd7756415ad9c78e80e850cbea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const std::string</type>
      <name>EventSourceId</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a11ae52b8b6e7519d0b3ea42561d6dccd</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>onKeyPressed</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a5072ad733814bd17d46e36ea8be4a4b4</anchor>
      <arglist>(KeyboardButton)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>onKeyReleased</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a000acdad189778380e4ac141dd4619cb</anchor>
      <arglist>(KeyboardButton)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::Mouse</name>
    <filename>a00057.html</filename>
    <base>engine::EventSourceBase</base>
    <base>engine::SlotHolder</base>
    <member kind="function">
      <type>ISignalManager *</type>
      <name>getSignalManager</name>
      <anchorfile>a00057.html</anchorfile>
      <anchor>a655d612dbf601fec2b116a1c94198247</anchor>
      <arglist>() const  override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assignSignal</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>afd9ce54a72b4dd397d82aff6c387d0c0</anchor>
      <arglist>(ISignal *signal)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeSignal</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>a5927b57f0d4fb8744dc0e8ec265e0136</anchor>
      <arglist>(ISignal *signal)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::NonCopyable</name>
    <filename>a00058.html</filename>
    <member kind="function">
      <type></type>
      <name>NonCopyable</name>
      <anchorfile>a00058.html</anchorfile>
      <anchor>a9f7cb34234d5117fbe31e0e82cf164b8</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~NonCopyable</name>
      <anchorfile>a00058.html</anchorfile>
      <anchor>a30addd3c42fbbe053a7484ed209ef8c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NonCopyable</name>
      <anchorfile>a00058.html</anchorfile>
      <anchor>a6018f0c6b722b97077bfb807f03f0f69</anchor>
      <arglist>(const NonCopyable &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>NonCopyable &amp;</type>
      <name>operator=</name>
      <anchorfile>a00058.html</anchorfile>
      <anchor>a21f1cc26f8f967d5c636e580cc728821</anchor>
      <arglist>(const NonCopyable &amp;)=delete</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::NonMoveable</name>
    <filename>a00059.html</filename>
    <member kind="function">
      <type></type>
      <name>NonMoveable</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>afc10190e7b658e00593b253c0d49cb35</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NonMoveable</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>a32b7d1f14280ffa724bd6404801a6bef</anchor>
      <arglist>(NonMoveable &amp;&amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>NonMoveable &amp;</type>
      <name>operator=</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>ae233a63d597305bc8a2175eab7e498d8</anchor>
      <arglist>(NonMoveable &amp;&amp;)=delete</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::PIMPLCopyable</name>
    <filename>a00060.html</filename>
    <templarg>T</templarg>
  </compound>
  <compound kind="class">
    <name>PIMPLCopyable&lt; EventSourceBase &gt;</name>
    <filename>a00060.html</filename>
  </compound>
  <compound kind="struct">
    <name>engine::PIMPLMoveable</name>
    <filename>a00061.html</filename>
    <templarg>T</templarg>
  </compound>
  <compound kind="class">
    <name>PIMPLMoveable&lt; EventSourceBase &gt;</name>
    <filename>a00061.html</filename>
  </compound>
  <compound kind="struct">
    <name>engine::PointerEqualTo</name>
    <filename>a00062.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>typename std::remove_pointer&lt; T &gt;::type</type>
      <name>ValueType</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>af485b6182246602f97c4f0bef182f799</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ValueType *</type>
      <name>RawPointerType</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>accdf0f2f7684859c103e277bc745f869</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::unique_ptr&lt; ValueType &gt;</type>
      <name>UniquePointerType</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>ad16a216e6217ae2f08c95f03fdd245cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::shared_ptr&lt; ValueType &gt;</type>
      <name>SharedPointerType</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>a30718c9509a5f19766f8d867ddd08011</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::weak_ptr&lt; ValueType &gt;</type>
      <name>WeakPointerType</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>ac6a2979606d67d0c973d3f73e7730651</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PointerEqualTo</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>a25356ec570fd1f0c1395c2ea7dcdc839</anchor>
      <arglist>(const RawPointerType &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>aa95f53dfe2393421d25b5bf6f458cb53</anchor>
      <arglist>(const RawPointerType &amp;o)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>abc68beffa9e32f7dd0caff6ce3d36e84</anchor>
      <arglist>(const UniquePointerType &amp;o)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>a5183273e9ba9a58234466b34adac373c</anchor>
      <arglist>(const SharedPointerType &amp;o)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>acdb87526d0e9c0aa8d235bf2e6cc5e97</anchor>
      <arglist>(const WeakPointerType &amp;o)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::ScopeExit</name>
    <filename>a00063.html</filename>
    <base protection="private">engine::NonCopyable</base>
  </compound>
  <compound kind="struct">
    <name>engine::ScopeExit_DeleteContainer</name>
    <filename>a00064.html</filename>
    <templarg></templarg>
    <base>engine::ScopeExit</base>
  </compound>
  <compound kind="class">
    <name>engine::Signal</name>
    <filename>a00065.html</filename>
    <templarg>Args</templarg>
    <base>engine::ISignal</base>
    <member kind="function">
      <type></type>
      <name>Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>ac27bc541be14d6ad516d858c3039df97</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a29c5d469f7f68d00e6895d1cf5121025</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>aba0c679c2026a6ddaafdac1f6a71cb70</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4dc6184edbd36dd8717d07c37a1f5fad</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnectAll</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4f3a4fcb844c23af742eac03e26bbc1b</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>emit</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>afbe3d238443fab207b5030ac8c77385c</anchor>
      <arglist>(Args...args)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Signal&lt; engine::StateBase * &gt;</name>
    <filename>a00065.html</filename>
    <base>engine::ISignal</base>
    <member kind="function">
      <type></type>
      <name>Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>ac27bc541be14d6ad516d858c3039df97</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a29c5d469f7f68d00e6895d1cf5121025</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>aba0c679c2026a6ddaafdac1f6a71cb70</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4dc6184edbd36dd8717d07c37a1f5fad</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnectAll</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4f3a4fcb844c23af742eac03e26bbc1b</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>emit</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>afbe3d238443fab207b5030ac8c77385c</anchor>
      <arglist>(Args...args)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Signal&lt; int32_t, int32_t &gt;</name>
    <filename>a00065.html</filename>
    <base>engine::ISignal</base>
    <member kind="function">
      <type></type>
      <name>Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>ac27bc541be14d6ad516d858c3039df97</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a29c5d469f7f68d00e6895d1cf5121025</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>aba0c679c2026a6ddaafdac1f6a71cb70</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4dc6184edbd36dd8717d07c37a1f5fad</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnectAll</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4f3a4fcb844c23af742eac03e26bbc1b</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>emit</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>afbe3d238443fab207b5030ac8c77385c</anchor>
      <arglist>(Args...args)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Signal&lt; int32_t, int32_t, int32_t &gt;</name>
    <filename>a00065.html</filename>
    <base>engine::ISignal</base>
    <member kind="function">
      <type></type>
      <name>Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>ac27bc541be14d6ad516d858c3039df97</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a29c5d469f7f68d00e6895d1cf5121025</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>aba0c679c2026a6ddaafdac1f6a71cb70</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4dc6184edbd36dd8717d07c37a1f5fad</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnectAll</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4f3a4fcb844c23af742eac03e26bbc1b</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>emit</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>afbe3d238443fab207b5030ac8c77385c</anchor>
      <arglist>(Args...args)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Signal&lt; KeyboardButton &gt;</name>
    <filename>a00065.html</filename>
    <base>engine::ISignal</base>
    <member kind="function">
      <type></type>
      <name>Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>ac27bc541be14d6ad516d858c3039df97</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a29c5d469f7f68d00e6895d1cf5121025</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>aba0c679c2026a6ddaafdac1f6a71cb70</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4dc6184edbd36dd8717d07c37a1f5fad</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnectAll</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4f3a4fcb844c23af742eac03e26bbc1b</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>emit</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>afbe3d238443fab207b5030ac8c77385c</anchor>
      <arglist>(Args...args)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Signal&lt; uint32_t, uint32_t &gt;</name>
    <filename>a00065.html</filename>
    <base>engine::ISignal</base>
    <member kind="function">
      <type></type>
      <name>Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>ac27bc541be14d6ad516d858c3039df97</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Signal</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a29c5d469f7f68d00e6895d1cf5121025</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>connect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>aba0c679c2026a6ddaafdac1f6a71cb70</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnect</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4dc6184edbd36dd8717d07c37a1f5fad</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disconnectAll</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4f3a4fcb844c23af742eac03e26bbc1b</anchor>
      <arglist>(T *holder)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>emit</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>afbe3d238443fab207b5030ac8c77385c</anchor>
      <arglist>(Args...args)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::SignalCaller</name>
    <filename>a00066.html</filename>
    <templarg>Ts</templarg>
    <member kind="function">
      <type></type>
      <name>SignalCaller</name>
      <anchorfile>a00066.html</anchorfile>
      <anchor>a0ac1c86918e5e9398dbb1cb587835ee1</anchor>
      <arglist>(const std::function&lt; void(Ts...)&gt; &amp;func)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00066.html</anchorfile>
      <anchor>a51aed6d729065df2d78aa8acab3e0eb9</anchor>
      <arglist>(const std::tuple&lt; Ts... &gt; &amp;args)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::function&lt; void(Ts...)&gt;</type>
      <name>createCallable</name>
      <anchorfile>a00066.html</anchorfile>
      <anchor>a6a9a7e7fc96f6921fc74b6386651afdc</anchor>
      <arglist>(T *t, void(T::*callback)(Ts...))</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::SignalManager</name>
    <filename>a00067.html</filename>
    <base>engine::ISignalManager</base>
    <base protection="private">engine::NonCopyable</base>
    <member kind="function">
      <type></type>
      <name>SignalManager</name>
      <anchorfile>a00067.html</anchorfile>
      <anchor>aba0cfccea1f10a10e9de9193fb62f358</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SignalManager</name>
      <anchorfile>a00067.html</anchorfile>
      <anchor>a1ad7e4f03ac0657b1ecf90c981053cde</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addTask</name>
      <anchorfile>a00067.html</anchorfile>
      <anchor>a5ac2136c91ad2e8a5e912f3f906d0073</anchor>
      <arglist>(std::unique_ptr&lt; ISignalTask &gt; task) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>a00067.html</anchorfile>
      <anchor>a4e2dbe6e08226abfca06f172606b102b</anchor>
      <arglist>() override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::SignalTask</name>
    <filename>a00068.html</filename>
    <templarg>Args</templarg>
    <base>engine::ISignalTask</base>
    <member kind="function">
      <type></type>
      <name>SignalTask</name>
      <anchorfile>a00068.html</anchorfile>
      <anchor>aa084db82b7369830ae2121d03c411045</anchor>
      <arglist>(std::weak_ptr&lt; SignalCaller&lt; Args... &gt;&gt; caller, const std::tuple&lt; Args... &gt; &amp;args)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00068.html</anchorfile>
      <anchor>a66e71dfc80f4320c2d5c260028b0bbff</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isExpired</name>
      <anchorfile>a00068.html</anchorfile>
      <anchor>af923108f7304a686bc4b7eeb41c35177</anchor>
      <arglist>() const  override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::Singleton</name>
    <filename>a00069.html</filename>
    <templarg>T</templarg>
    <base protection="private">engine::NonCopyable</base>
    <base protection="private">engine::NonMoveable</base>
    <member kind="function" static="yes">
      <type>static T *</type>
      <name>getInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a90ed1f21b1811a569eafccc78fcd12ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>createInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a571e434c8ff771bf65de40f8a7b22076</anchor>
      <arglist>(Args...args)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>releaseInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a3fbed1f6a78cdf1d0c11467a3be61841</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Singleton&lt; Context &gt;</name>
    <filename>a00069.html</filename>
    <base protection="private">engine::NonCopyable</base>
    <base protection="private">engine::NonMoveable</base>
    <member kind="function" static="yes">
      <type>static Context *</type>
      <name>getInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a90ed1f21b1811a569eafccc78fcd12ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>createInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a571e434c8ff771bf65de40f8a7b22076</anchor>
      <arglist>(Args...args)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>releaseInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a3fbed1f6a78cdf1d0c11467a3be61841</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Singleton&lt; VersionBase&lt; VersionClass &gt; &gt;</name>
    <filename>a00069.html</filename>
    <base protection="private">engine::NonCopyable</base>
    <base protection="private">engine::NonMoveable</base>
    <member kind="function" static="yes">
      <type>static VersionBase&lt; VersionClass &gt; *</type>
      <name>getInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a90ed1f21b1811a569eafccc78fcd12ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>createInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a571e434c8ff771bf65de40f8a7b22076</anchor>
      <arglist>(Args...args)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>releaseInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a3fbed1f6a78cdf1d0c11467a3be61841</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::SlotHolder</name>
    <filename>a00070.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual ISignalManager *</type>
      <name>getSignalManager</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>add6d89f31a2677b29a52f241d0431c13</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>assignSignal</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>afd9ce54a72b4dd397d82aff6c387d0c0</anchor>
      <arglist>(ISignal *signal)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeSignal</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>a5927b57f0d4fb8744dc0e8ec265e0136</anchor>
      <arglist>(ISignal *signal)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::StandardApplicationParameter</name>
    <filename>a00071.html</filename>
    <base>engine::IApplicationParameter</base>
    <member kind="function">
      <type></type>
      <name>StandardApplicationParameter</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>ab0088697771492ee97bdaa9b09a97c08</anchor>
      <arglist>(uint32_t nParams, char *parameters[])</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~StandardApplicationParameter</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>a91c65b5c5cc6c87005fb618b61daef5a</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; std::string &gt; &amp;</type>
      <name>getParameters</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>ae482854d2439758cfd1d2c710c621b4f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>getBinaryName</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>a5d29ea3dfb725dc1a386926896b5a48a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>StandardApplicationParameter</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>ab09e6ae2065a3a1e1fc4461d5f25c46b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>aaf7d27892d7fbad5573099a4fabb6218</anchor>
      <arglist>(uint32_t nParams, const std::vector&lt; std::string &gt; &amp;parameters)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::StateBase</name>
    <filename>a00072.html</filename>
    <base>engine::NonCopyable</base>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~StateBase</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>ab664691d7ef22f9764816ab9aaf7d537</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>aa80ea4f74acd99c5b51d61e397b84e0b</anchor>
      <arglist>(StateStack *stack)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>destroy</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>a28c40b43d8852235b3f2ea4ca39c0cad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resume</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>a7a109867f252655aa625f8421071fa23</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pause</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>acc1a281ee5cd9192fb7a703c5ef8c49b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>a90b80b1002ed942c2f3b8dd9965cfba0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>render</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>a0e52521456a98ab4b8a58ba01d356836</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInitialized</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>a73a808c7f866e21ab85b694d726159eb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trace</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>a369f9b474222dfe2109e6d15630157db</anchor>
      <arglist>(std::ostream &amp;) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>StateBase</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>aee338ee916b37c21d986e2f0c6a3cf01</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>isActive</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>a9dbd0e91cd8812be304df62aa8bca558</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>isLeaving</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>aaec38f3ff2f0af1bffcad4054f92f5f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>changeState</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>a95a7fffdec13deafa7855755f6f5f153</anchor>
      <arglist>(std::unique_ptr&lt; StateBase &gt; nextState)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>exitState</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>a04227376a170bdb851e0e03a4949f564</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Signal&lt; StateBase * &gt;</type>
      <name>stateChanged</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>aa585934f221ce16ddac54f79c759e30e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Signal</type>
      <name>stateTerminated</name>
      <anchorfile>a00072.html</anchorfile>
      <anchor>aa833cf334d703956398b0eab5353fb14</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::StateStack</name>
    <filename>a00073.html</filename>
    <base protection="private">engine::NonCopyable</base>
    <base protection="private">engine::NonMoveable</base>
    <member kind="typedef">
      <type>std::list&lt; StateBase * &gt;</type>
      <name>StateList</name>
      <anchorfile>a00073.html</anchorfile>
      <anchor>a866f3ce726d328dc3488f3300b94be07</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>StateStack</name>
      <anchorfile>a00073.html</anchorfile>
      <anchor>af80814eae37384bbbf07f3c041ff9489</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~StateStack</name>
      <anchorfile>a00073.html</anchorfile>
      <anchor>a1c5c62604825cc9e4395212cd2986829</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>a00073.html</anchorfile>
      <anchor>a129b751979654c033dfbb5595519db48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>render</name>
      <anchorfile>a00073.html</anchorfile>
      <anchor>a948f666845a6bbebc6f629a3eef8de0b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pushState</name>
      <anchorfile>a00073.html</anchorfile>
      <anchor>aae3b3caef3cf8dfd7ba9ea0232b5babd</anchor>
      <arglist>(std::unique_ptr&lt; StateBase &gt; state)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>popState</name>
      <anchorfile>a00073.html</anchorfile>
      <anchor>ad4332c156e0169fcde04044acb59928d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trace</name>
      <anchorfile>a00073.html</anchorfile>
      <anchor>a7d05f3d0f8ca93a48911bb14558314d4</anchor>
      <arglist>(std::ostream &amp;os) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isEmpty</name>
      <anchorfile>a00073.html</anchorfile>
      <anchor>a07e9947e97bb7e5ad5533d68f0791429</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::test::TestAssertException</name>
    <filename>a00074.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::test::TestCase</name>
    <filename>a00075.html</filename>
    <templarg></templarg>
    <templarg>func</templarg>
    <base>engine::test::ITestCase</base>
  </compound>
  <compound kind="class">
    <name>engine::test::TestManager</name>
    <filename>a00076.html</filename>
    <base protection="private">engine::NonCopyable</base>
  </compound>
  <compound kind="class">
    <name>engine::test::TestSuite</name>
    <filename>a00077.html</filename>
  </compound>
  <compound kind="struct">
    <name>engine::UnsupportedFeature</name>
    <filename>a00078.html</filename>
    <member kind="function">
      <type></type>
      <name>UnsupportedFeature</name>
      <anchorfile>a00078.html</anchorfile>
      <anchor>adf506e7a80acd5615803065c18b55b8d</anchor>
      <arglist>(const std::string &amp;error)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>UnsupportedFeature</name>
      <anchorfile>a00078.html</anchorfile>
      <anchor>a0774b1ed4a1653d17c14053dc87e427e</anchor>
      <arglist>(const char *error)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::VersionBase</name>
    <filename>a00079.html</filename>
    <templarg>VersionClass</templarg>
    <base>Singleton&lt; VersionBase&lt; VersionClass &gt; &gt;</base>
    <member kind="function">
      <type>int32_t</type>
      <name>getMajor</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a87db56a6b48379927ea2c34053ad11d8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>getMinor</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a9e3c537a417ce0bfbcc6758ad5ae5cb5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>getCounter</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a22329ec00668f53aaf4a4efc68d49f93</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>getYear</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>af8f407400b6b4994c1cd3b243ef84b05</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>getMonth</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a4a3f44823b8caa24943a954385184de2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int32_t</type>
      <name>getDay</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a05c80a133cb8aa10d1c18088f163c206</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getString</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>aa0b506e6d23023c3efd3a312a39a336d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a92759ed17bf0e3976ba1bf846b7e21c9</anchor>
      <arglist>(const VersionBase&lt; OVersionClass &gt; &amp;o) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a4225f1bc4cbcf482bfe688cf0a60fc21</anchor>
      <arglist>(const VersionBase&lt; OVersionClass &gt; &amp;o) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a4bff2ae98a2d5883e6dbab5833a51cd7</anchor>
      <arglist>(const VersionBase&lt; OVersionClass &gt; &amp;o) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;=</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a564b9166e177e8657f87f19447aea0cf</anchor>
      <arglist>(const VersionBase&lt; OVersionClass &gt; &amp;o) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;=</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>abd9cbd90f53ff3b5304588349c1b4b7c</anchor>
      <arglist>(const VersionBase&lt; OVersionClass &gt; &amp;o) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a87adeb21177fa070dd7fc6a9ffbda5b2</anchor>
      <arglist>(const VersionBase&lt; OVersionClass &gt; &amp;o) const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static VersionBase&lt; VersionClass &gt; *</type>
      <name>getInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a90ed1f21b1811a569eafccc78fcd12ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>createInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a571e434c8ff771bf65de40f8a7b22076</anchor>
      <arglist>(Args...args)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>releaseInstance</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a3fbed1f6a78cdf1d0c11467a3be61841</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>VersionBase</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a706934249d82028c323d45749a13d884</anchor>
      <arglist>()=default</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::version::VersionDef</name>
    <filename>a00080.html</filename>
  </compound>
  <compound kind="class">
    <name>engine::winapi::WinApiApplicationParameter</name>
    <filename>a00081.html</filename>
    <base>engine::StandardApplicationParameter</base>
    <member kind="function">
      <type></type>
      <name>WinApiApplicationParameter</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>af7fef7fdba7239b1b01e9ba9c46c1a32</anchor>
      <arglist>(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdShow)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~WinApiApplicationParameter</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a8cf7f2740093b195aa980b9791b2b4cb</anchor>
      <arglist>() override</arglist>
    </member>
    <member kind="function">
      <type>HINSTANCE</type>
      <name>getInstance</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a35f806d57b22fa9bcab1b6391a8060b7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getCmdShow</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a30232e7cd9fce28ce65b7b3b7325f69f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const std::vector&lt; std::string &gt; &amp;</type>
      <name>getParameters</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>ae482854d2439758cfd1d2c710c621b4f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>getBinaryName</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>a5d29ea3dfb725dc1a386926896b5a48a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>aaf7d27892d7fbad5573099a4fabb6218</anchor>
      <arglist>(uint32_t nParams, const std::vector&lt; std::string &gt; &amp;parameters)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::Window</name>
    <filename>a00082.html</filename>
    <base>engine::EventSourceBase</base>
    <member kind="function">
      <type></type>
      <name>Window</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a6adceceb01e5ed546282c5ea2d09af88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Window</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a3bf48ba460f021664ad27f27509cf473</anchor>
      <arglist>(const WindowParameter &amp;parameter)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Window</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a9540302516f5eda30facee89517346ed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const WindowParameter &amp;</type>
      <name>getParameters</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>afbb0f8b825f17fbf8f434c4ab9ae5f8d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPosition</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>ad6874b68c5cd0b59ec75ac8ad15f2a3a</anchor>
      <arglist>(int32_t x, int32_t y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWidth</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a3435c3bf0e07492ec77f3977c9b5e355</anchor>
      <arglist>(uint32_t width)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHeight</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a87b8b6f2c1a08327d4010e2b6aceb319</anchor>
      <arglist>(uint32_t height)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSize</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>aefaae1015e22521e0a0168633a7d413f</anchor>
      <arglist>(uint32_t width, uint32_t height)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFullScreen</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a9429ac0c042cc998ecbedb1c13c0bc9a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowClosed</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a5bb494c228eb398d6893327fcf03d2d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; uint32_t, uint32_t &gt;</type>
      <name>windowSizeChanged</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a20978a09b8843aa8960dc9d3a989b11a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; uint32_t, uint32_t &gt;</type>
      <name>windowFrameBufferSizeChanged</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a0c6ef7abcac1063c91a84123c81f9347</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; int32_t, int32_t &gt;</type>
      <name>windowMoved</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a4bdb42d789ed9587ff8f840065752506</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowInFocus</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a2a81dc83b5e8433eb39e1ca8263d0c0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowOutFocus</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>af6f8cc0d616685683d5c6b52b4cc07d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>WindowParameter</type>
      <name>_parameters</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>aae1d39f3df529497025772967ac578a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_fullScreen</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a5167b1318668d7639112ce85eafc6c8b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::WindowEnvironmentBuilder</name>
    <filename>a00083.html</filename>
    <base>engine::BaseBuilder</base>
    <member kind="function">
      <type></type>
      <name>~WindowEnvironmentBuilder</name>
      <anchorfile>a00083.html</anchorfile>
      <anchor>a193f03159de54e2db47751504e523180</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>WindowEnvironmentBuilder</name>
      <anchorfile>a00083.html</anchorfile>
      <anchor>a6a0e846406df6a3f23a8327d248a6534</anchor>
      <arglist>(WindowEnvironmentBuilder &amp;&amp;o)</arglist>
    </member>
    <member kind="function">
      <type>BuildFinalizer</type>
      <name>build</name>
      <anchorfile>a00083.html</anchorfile>
      <anchor>adbe84bb40e32bc0d0b9a97dd63624610</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>addModule</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52fb449fadc5d3a074e3fc7bfb56744b</anchor>
      <arglist>(const ContextModuleType value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setApplication</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a20c5dafa6892142bc352c13a5f3ac09a</anchor>
      <arglist>(std::unique_ptr&lt; Application &gt; app)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setWindowManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a641fb06484bdb07220f445f14db8c0e7</anchor>
      <arglist>(std::unique_ptr&lt; WindowManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setEventManager</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a52b490a3ef4d2a5b5b7e8e0f82d9a27c</anchor>
      <arglist>(std::unique_ptr&lt; EventManager &gt; manager)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setInitialized</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>af23e3bdfb30ca9f2076cacc9029d96c2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::glfw::WindowImpl</name>
    <filename>a00084.html</filename>
    <base>engine::Window</base>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>a00084.html</anchorfile>
      <anchor>a6bd72585d8e7376ae77fd1df993a7d42</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPositionImp</name>
      <anchorfile>a00084.html</anchorfile>
      <anchor>af52abedfc7695f94f32167d52e501b3d</anchor>
      <arglist>(int32_t x, int32_t y) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWidthImpl</name>
      <anchorfile>a00084.html</anchorfile>
      <anchor>a2a42c1ce8e90c3adef80e5973b91bb38</anchor>
      <arglist>(uint32_t width) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHeightImpl</name>
      <anchorfile>a00084.html</anchorfile>
      <anchor>a877ca64eee45c4f5abc766c4164e316c</anchor>
      <arglist>(uint32_t height) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSizeImpl</name>
      <anchorfile>a00084.html</anchorfile>
      <anchor>a226cde7add1fb27044e3eccd167f361f</anchor>
      <arglist>(uint32_t width, uint32_t height) override</arglist>
    </member>
    <member kind="function">
      <type>const WindowParameter &amp;</type>
      <name>getParameters</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>afbb0f8b825f17fbf8f434c4ab9ae5f8d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPosition</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>ad6874b68c5cd0b59ec75ac8ad15f2a3a</anchor>
      <arglist>(int32_t x, int32_t y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWidth</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a3435c3bf0e07492ec77f3977c9b5e355</anchor>
      <arglist>(uint32_t width)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHeight</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a87b8b6f2c1a08327d4010e2b6aceb319</anchor>
      <arglist>(uint32_t height)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSize</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>aefaae1015e22521e0a0168633a7d413f</anchor>
      <arglist>(uint32_t width, uint32_t height)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFullScreen</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a9429ac0c042cc998ecbedb1c13c0bc9a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowClosed</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a5bb494c228eb398d6893327fcf03d2d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; uint32_t, uint32_t &gt;</type>
      <name>windowSizeChanged</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a20978a09b8843aa8960dc9d3a989b11a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; uint32_t, uint32_t &gt;</type>
      <name>windowFrameBufferSizeChanged</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a0c6ef7abcac1063c91a84123c81f9347</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; int32_t, int32_t &gt;</type>
      <name>windowMoved</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a4bdb42d789ed9587ff8f840065752506</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowInFocus</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a2a81dc83b5e8433eb39e1ca8263d0c0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowOutFocus</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>af6f8cc0d616685683d5c6b52b4cc07d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>WindowParameter</type>
      <name>_parameters</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>aae1d39f3df529497025772967ac578a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_fullScreen</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a5167b1318668d7639112ce85eafc6c8b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::sdl::WindowImpl</name>
    <filename>a00085.html</filename>
    <base>engine::Window</base>
    <member kind="function">
      <type></type>
      <name>WindowImpl</name>
      <anchorfile>a00085.html</anchorfile>
      <anchor>abe5d2ca094660b7bbb3253a2e59f0c40</anchor>
      <arglist>(SDL_Window *window, const std::string &amp;title=&quot;Window&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>a00085.html</anchorfile>
      <anchor>a022aa2c636b4586fce459140d63dd4a3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPositionImp</name>
      <anchorfile>a00085.html</anchorfile>
      <anchor>a1e3bb0cf9a7774291fd326b52e446c50</anchor>
      <arglist>(int32_t x, int32_t y) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWidthImpl</name>
      <anchorfile>a00085.html</anchorfile>
      <anchor>a4291d464432a5e432675147978427046</anchor>
      <arglist>(uint32_t width) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHeightImpl</name>
      <anchorfile>a00085.html</anchorfile>
      <anchor>aec8cd8820617c3c8bf03c0f14ca39c29</anchor>
      <arglist>(uint32_t height) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSizeImpl</name>
      <anchorfile>a00085.html</anchorfile>
      <anchor>ac197d9aeb0ab4d84d6b1aaaa3569df49</anchor>
      <arglist>(uint32_t width, uint32_t height) override</arglist>
    </member>
    <member kind="function">
      <type>SDL_Window *</type>
      <name>getSDLWindow</name>
      <anchorfile>a00085.html</anchorfile>
      <anchor>a2ac40d78891bc1baa892ae81834c040d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const WindowParameter &amp;</type>
      <name>getParameters</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>afbb0f8b825f17fbf8f434c4ab9ae5f8d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPosition</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>ad6874b68c5cd0b59ec75ac8ad15f2a3a</anchor>
      <arglist>(int32_t x, int32_t y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWidth</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a3435c3bf0e07492ec77f3977c9b5e355</anchor>
      <arglist>(uint32_t width)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHeight</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a87b8b6f2c1a08327d4010e2b6aceb319</anchor>
      <arglist>(uint32_t height)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSize</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>aefaae1015e22521e0a0168633a7d413f</anchor>
      <arglist>(uint32_t width, uint32_t height)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFullScreen</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a9429ac0c042cc998ecbedb1c13c0bc9a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowClosed</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a5bb494c228eb398d6893327fcf03d2d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; uint32_t, uint32_t &gt;</type>
      <name>windowSizeChanged</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a20978a09b8843aa8960dc9d3a989b11a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; uint32_t, uint32_t &gt;</type>
      <name>windowFrameBufferSizeChanged</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a0c6ef7abcac1063c91a84123c81f9347</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; int32_t, int32_t &gt;</type>
      <name>windowMoved</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a4bdb42d789ed9587ff8f840065752506</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowInFocus</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a2a81dc83b5e8433eb39e1ca8263d0c0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowOutFocus</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>af6f8cc0d616685683d5c6b52b4cc07d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>WindowParameter</type>
      <name>_parameters</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>aae1d39f3df529497025772967ac578a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_fullScreen</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a5167b1318668d7639112ce85eafc6c8b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::winapi::WindowImpl</name>
    <filename>a00086.html</filename>
    <base>engine::Window</base>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>a00086.html</anchorfile>
      <anchor>a21a3e5b9d64ffe9a2db8062a603ee076</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPositionImp</name>
      <anchorfile>a00086.html</anchorfile>
      <anchor>a8a3dd7b1047ebd09cc8157a98c6d6c72</anchor>
      <arglist>(int32_t x, int32_t y) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWidthImpl</name>
      <anchorfile>a00086.html</anchorfile>
      <anchor>aa0b9a89ff73b90182d48152ac4b4f4dc</anchor>
      <arglist>(uint32_t width) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHeightImpl</name>
      <anchorfile>a00086.html</anchorfile>
      <anchor>a298a79f73edccaa8d673f90d23b8f1b8</anchor>
      <arglist>(uint32_t height) override</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSizeImpl</name>
      <anchorfile>a00086.html</anchorfile>
      <anchor>a44300292fa46bdd0d8eb9ee558750192</anchor>
      <arglist>(uint32_t width, uint32_t height) override</arglist>
    </member>
    <member kind="function">
      <type>HWND</type>
      <name>getWindowHandler</name>
      <anchorfile>a00086.html</anchorfile>
      <anchor>aba8c0c26368247565159027ae8efb780</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const WindowParameter &amp;</type>
      <name>getParameters</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>afbb0f8b825f17fbf8f434c4ab9ae5f8d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setPosition</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>ad6874b68c5cd0b59ec75ac8ad15f2a3a</anchor>
      <arglist>(int32_t x, int32_t y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWidth</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a3435c3bf0e07492ec77f3977c9b5e355</anchor>
      <arglist>(uint32_t width)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setHeight</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a87b8b6f2c1a08327d4010e2b6aceb319</anchor>
      <arglist>(uint32_t height)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setSize</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>aefaae1015e22521e0a0168633a7d413f</anchor>
      <arglist>(uint32_t width, uint32_t height)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isFullScreen</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a9429ac0c042cc998ecbedb1c13c0bc9a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowClosed</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a5bb494c228eb398d6893327fcf03d2d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; uint32_t, uint32_t &gt;</type>
      <name>windowSizeChanged</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a20978a09b8843aa8960dc9d3a989b11a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; uint32_t, uint32_t &gt;</type>
      <name>windowFrameBufferSizeChanged</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a0c6ef7abcac1063c91a84123c81f9347</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal&lt; int32_t, int32_t &gt;</type>
      <name>windowMoved</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a4bdb42d789ed9587ff8f840065752506</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowInFocus</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a2a81dc83b5e8433eb39e1ca8263d0c0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>engine::Signal</type>
      <name>windowOutFocus</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>af6f8cc0d616685683d5c6b52b4cc07d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>WindowParameter</type>
      <name>_parameters</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>aae1d39f3df529497025772967ac578a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>_fullScreen</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a5167b1318668d7639112ce85eafc6c8b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::WindowManager</name>
    <filename>a00087.html</filename>
    <base protection="private">engine::NonCopyable</base>
    <member kind="function">
      <type></type>
      <name>WindowManager</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a6749235b97d99fd37e3364b5028c05f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~WindowManager</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a86a0bbdde5137d9fefdb3fd3d2f4ba27</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual uint32_t</type>
      <name>getMonitorCount</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>ab0508dca59ae0d5366158385b75ae8b6</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual uint32_t</type>
      <name>getMainMonitorId</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>ae1c80e3385179a2908316ac74c2fc520</anchor>
      <arglist>() const  =0</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a863ac648c2c2a93a57c4a898fb176718</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createFullScreenMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9c2adc3003612cafb99fd7a156bc9655</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createSecondaryWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>afc8f953d7aa1e2822b8ced1e5b855ab8</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title, Window *mainWindow)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createSecondaryFullScreenWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a8d3b6392e5389e7e5706f92ceed96fa0</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId, Window *mainWindow)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>destroyWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>aecfb9aa6471ecf82e5c76a96440c275c</anchor>
      <arglist>(Window *)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>getMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a7ccb3265cab90117a4face1c5ebb5e29</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Window *</type>
      <name>getMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>aa59c328988c32399328f8f38c5210275</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Window * &gt;</type>
      <name>getAllWindows</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9aac4dcdd92008cd8602b7456be6260a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDriverParameter</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9aaa765ab360c7093dd1f1d3f5f3d621</anchor>
      <arglist>(const DriverInitParameters &amp;defaultParameters)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual Window *</type>
      <name>createMainWindowImpl</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>ad5dba47d5f1da2abfa9bacffd318ba3d</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual Window *</type>
      <name>createFullScreenMainWindowImpl</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a3af32a24c80a711eb8473d54876c4d28</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual Window *</type>
      <name>createSecondaryWindowImpl</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a3944290d64b7d8f23764464f5f2df82f</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title, Window *mainWindow)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual Window *</type>
      <name>createSecondaryFullScreenWindowImpl</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a62c22afc4f34aa5447f45239702ac67a</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId, Window *mainWindow)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual std::unique_ptr&lt; Driver &gt;</type>
      <name>createDriverForWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a640d280cbddc70431a12c6ffb8fb34fd</anchor>
      <arglist>(const DriverInitParameters &amp;, Window *) const  =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::winapi::WindowManagerImpl</name>
    <filename>a00088.html</filename>
    <base>engine::WindowManager</base>
    <member kind="function">
      <type>uint32_t</type>
      <name>getMonitorCount</name>
      <anchorfile>a00088.html</anchorfile>
      <anchor>afa93bde2dfc7d722c236f2a2c51b45af</anchor>
      <arglist>() const  override</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>getMainMonitorId</name>
      <anchorfile>a00088.html</anchorfile>
      <anchor>a549d762ba32d525e574c06d8bb103255</anchor>
      <arglist>() const  override</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a863ac648c2c2a93a57c4a898fb176718</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createFullScreenMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9c2adc3003612cafb99fd7a156bc9655</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createSecondaryWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>afc8f953d7aa1e2822b8ced1e5b855ab8</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title, Window *mainWindow)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createSecondaryFullScreenWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a8d3b6392e5389e7e5706f92ceed96fa0</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId, Window *mainWindow)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>destroyWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>aecfb9aa6471ecf82e5c76a96440c275c</anchor>
      <arglist>(Window *)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>getMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a7ccb3265cab90117a4face1c5ebb5e29</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Window *</type>
      <name>getMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>aa59c328988c32399328f8f38c5210275</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Window * &gt;</type>
      <name>getAllWindows</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9aac4dcdd92008cd8602b7456be6260a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDriverParameter</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9aaa765ab360c7093dd1f1d3f5f3d621</anchor>
      <arglist>(const DriverInitParameters &amp;defaultParameters)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createMainWindowImpl</name>
      <anchorfile>a00088.html</anchorfile>
      <anchor>a4c3adbbf883d7bbc15e17cc4c868ee14</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createFullScreenMainWindowImpl</name>
      <anchorfile>a00088.html</anchorfile>
      <anchor>a9684f59d2995f89182e039e7591a59cc</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createSecondaryWindowImpl</name>
      <anchorfile>a00088.html</anchorfile>
      <anchor>ac82c286d1666a12ea3fa807958ff546d</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title, Window *mainWindow) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createSecondaryFullScreenWindowImpl</name>
      <anchorfile>a00088.html</anchorfile>
      <anchor>acb25d1f39aec8507fd80bdff20d7abc3</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId, Window *mainWindow) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::unique_ptr&lt; Driver &gt;</type>
      <name>createDriverForWindow</name>
      <anchorfile>a00088.html</anchorfile>
      <anchor>aced29776a0025033bb3fb92a821a5deb</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *) const  override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::sdl::WindowManagerImpl</name>
    <filename>a00089.html</filename>
    <base>engine::WindowManager</base>
    <member kind="function">
      <type>uint32_t</type>
      <name>getMonitorCount</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a1f52cf717fa2ca568833416b126975cd</anchor>
      <arglist>() const  override</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>getMainMonitorId</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a21001322db84287f4ada31f645e0da93</anchor>
      <arglist>() const  override</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a863ac648c2c2a93a57c4a898fb176718</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createFullScreenMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9c2adc3003612cafb99fd7a156bc9655</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createSecondaryWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>afc8f953d7aa1e2822b8ced1e5b855ab8</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title, Window *mainWindow)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createSecondaryFullScreenWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a8d3b6392e5389e7e5706f92ceed96fa0</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId, Window *mainWindow)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>destroyWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>aecfb9aa6471ecf82e5c76a96440c275c</anchor>
      <arglist>(Window *)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>getMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a7ccb3265cab90117a4face1c5ebb5e29</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Window *</type>
      <name>getMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>aa59c328988c32399328f8f38c5210275</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Window * &gt;</type>
      <name>getAllWindows</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9aac4dcdd92008cd8602b7456be6260a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDriverParameter</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9aaa765ab360c7093dd1f1d3f5f3d621</anchor>
      <arglist>(const DriverInitParameters &amp;defaultParameters)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createMainWindowImpl</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a724b94a86d7fa24a317ca2400e19c3a6</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createFullScreenMainWindowImpl</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>ae345cf8a66a523782ea4920ffaa04f96</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createSecondaryWindowImpl</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a31aaa0f6700a06b1f6da638577673bce</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title, Window *mainWindow) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createSecondaryFullScreenWindowImpl</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a28e27c9fe4ec728ff2a88b3ee7286884</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId, Window *mainWindow) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::unique_ptr&lt; Driver &gt;</type>
      <name>createDriverForWindow</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>ac99173816ec5a2fc4a739aba8b566953</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *) const  override</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::glfw::WindowManagerImpl</name>
    <filename>a00090.html</filename>
    <base>engine::WindowManager</base>
    <member kind="function">
      <type>uint32_t</type>
      <name>getMonitorCount</name>
      <anchorfile>a00090.html</anchorfile>
      <anchor>a40ee7fc65955826dede09f35e3aa4815</anchor>
      <arglist>() const  override</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>getMainMonitorId</name>
      <anchorfile>a00090.html</anchorfile>
      <anchor>a02afdb8c94a0dc9c8e052901e44676ab</anchor>
      <arglist>() const  override</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a863ac648c2c2a93a57c4a898fb176718</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createFullScreenMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9c2adc3003612cafb99fd7a156bc9655</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createSecondaryWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>afc8f953d7aa1e2822b8ced1e5b855ab8</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title, Window *mainWindow)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>createSecondaryFullScreenWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a8d3b6392e5389e7e5706f92ceed96fa0</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId, Window *mainWindow)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>destroyWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>aecfb9aa6471ecf82e5c76a96440c275c</anchor>
      <arglist>(Window *)</arglist>
    </member>
    <member kind="function">
      <type>Window *</type>
      <name>getMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a7ccb3265cab90117a4face1c5ebb5e29</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const Window *</type>
      <name>getMainWindow</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>aa59c328988c32399328f8f38c5210275</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Window * &gt;</type>
      <name>getAllWindows</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9aac4dcdd92008cd8602b7456be6260a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDriverParameter</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a9aaa765ab360c7093dd1f1d3f5f3d621</anchor>
      <arglist>(const DriverInitParameters &amp;defaultParameters)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createMainWindowImpl</name>
      <anchorfile>a00090.html</anchorfile>
      <anchor>ab33ae118afb5a7048c61d437e54b5c43</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createFullScreenMainWindowImpl</name>
      <anchorfile>a00090.html</anchorfile>
      <anchor>acb8925ac309ba2705221a8db7357bb60</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createSecondaryWindowImpl</name>
      <anchorfile>a00090.html</anchorfile>
      <anchor>aed46f77f80b40c2a2e6ec23cb5dc5bf7</anchor>
      <arglist>(const WindowParameter &amp;parameters, const std::string &amp;title, Window *mainWindow) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Window *</type>
      <name>createSecondaryFullScreenWindowImpl</name>
      <anchorfile>a00090.html</anchorfile>
      <anchor>a7fce1ce88b1aa3ec24b0b78fd5e56a64</anchor>
      <arglist>(const uint32_t width, const uint32_t height, const std::string &amp;title, uint32_t monitorId, Window *mainWindow) override</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::unique_ptr&lt; Driver &gt;</type>
      <name>createDriverForWindow</name>
      <anchorfile>a00090.html</anchorfile>
      <anchor>a8d7410a6f39bc3f2e4255939e2549e9b</anchor>
      <arglist>(const DriverInitParameters &amp;params, Window *) const  override</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>engine::WindowParameter</name>
    <filename>a00091.html</filename>
    <member kind="function">
      <type></type>
      <name>WindowParameter</name>
      <anchorfile>a00091.html</anchorfile>
      <anchor>ac4c0175c0aa56acbcd3e8ba73b803821</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>WindowParameter</name>
      <anchorfile>a00091.html</anchorfile>
      <anchor>a0872d548da562e6a4ed40f12d151b6a5</anchor>
      <arglist>(uint32_t x, uint32_t y, uint32_t width, uint32_t height)</arglist>
    </member>
    <member kind="variable">
      <type>int32_t</type>
      <name>x</name>
      <anchorfile>a00091.html</anchorfile>
      <anchor>a1ae6e0c7a9ad94617c7b8e3c54faabf5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int32_t</type>
      <name>y</name>
      <anchorfile>a00091.html</anchorfile>
      <anchor>a9f6e5adf0cb73c89ebdfe0c993d299fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>width</name>
      <anchorfile>a00091.html</anchorfile>
      <anchor>a068d271ecfc95b7c3dcf19e43b2a65f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>height</name>
      <anchorfile>a00091.html</anchorfile>
      <anchor>a9a2039d074f22d4c639ef5254fc30fb7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>engine::winapi::WinProcExtension</name>
    <filename>a00092.html</filename>
    <base>engine::IModuleExtension</base>
    <base protection="private">engine::NonCopyable</base>
    <base protection="private">engine::NonMoveable</base>
  </compound>
  <compound kind="struct">
    <name>engine::WrongStateError</name>
    <filename>a00093.html</filename>
    <member kind="function">
      <type></type>
      <name>WrongStateError</name>
      <anchorfile>a00093.html</anchorfile>
      <anchor>a2c4332149aa8e41ffcef52a21727d03d</anchor>
      <arglist>(const std::string &amp;error)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>WrongStateError</name>
      <anchorfile>a00093.html</anchorfile>
      <anchor>a279d5a0c8c39380af223092423d1f56c</anchor>
      <arglist>(const char *error)</arglist>
    </member>
  </compound>
</tagfile>
