cmake_minimum_required(VERSION 3.10)
project(XPlay)
set(CMAKE_CXX_STANDARD 11)

set(MY_LIBRARY_DIR /usr/local/Cellar)
set(FFMPEG_DIR ${MY_LIBRARY_DIR}/ffmpeg/4.1.3_1) # FFmpeg的安装目录，可以通过命令"brew info ffmpeg"获取
set(SDL_DIR ${MY_LIBRARY_DIR}/sdl2/2.0.9_1/)

include_directories(${FFMPEG_DIR}/include/
        ${SDL_DIR}/include/) # 头文件搜索路径
link_directories(${FFMPEG_DIR}/lib/
        ${SDL_DIR}/lib/) # 动态链接库或静态链接库的搜索路径

add_executable(XPlay main.cpp IDemux.cpp IDemux.h FFDemux.cpp FFDemux.h XData.cpp XData.h XLog.cpp XLog.h XThread.cpp XThread.h IObserver.cpp IObserver.h IDecode.cpp IDecode.h FFDecode.cpp FFDecode.h XParameter.cpp XParameter.h IVideoView.cpp IVideoView.h SDLVideoView.cpp SDLVideoView.h IResample.cpp IResample.h FFResample.cpp FFResample.h IAudioPlay.cpp IAudioPlay.h SDLAudioPlay.cpp SDLAudioPlay.h IPlayer.cpp IPlayer.h IPlayerBuilder.cpp IPlayerBuilder.h FFPlayerBuilder.cpp FFPlayerBuilder.h IPlayerProxy.cpp IPlayerProxy.h)

# 添加链接库
target_link_libraries(
        XPlay
        avcodec
        avdevice
        avfilter
        avformat
        swresample

        SDL2
)