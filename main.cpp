#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}   

int main(int argc, const char *argv[]) 
{
    if (argc < 2) {
        std::cout << "You need to specify a media file in the command line.\n";
        return -1;
    }

    AVFormatContext *pFormatContext = avformat_alloc_context();
    if (!pFormatContext) {
        std::cout << "Could not allocate memory for Format Context\n";
        return -1;
    }

    const char *file_path = argv[1];
    if (avformat_open_input(&pFormatContext, argv[1], NULL, NULL) != 0) {
        std::cout << "Could not open the file" << std::endl;
        return -1;
    }

    if (avformat_find_stream_info(pFormatContext,  NULL) < 0) {
        std::cout << "Could not get the stream info" << std::endl;
        return -1;
    }

    if(pFormatContext->nb_streams == 0){
        std::cout << "File does not have streams" << std::endl;
        return 0;
    }
    std::printf("File has %d streams:\n", pFormatContext->nb_streams);

    for (int i = 0; i < pFormatContext->nb_streams; i++)
    {
        AVCodecParameters *pCodecParameters = pFormatContext->streams[i]->codecpar;

        AVCodec *pCodec = NULL;
        pCodec = avcodec_find_decoder(pCodecParameters->codec_id);

        const char* szCodecName = NULL;
        if (pCodec==NULL)
            szCodecName = "unsupported";
        else
            szCodecName = pCodec->name;

        if (pCodecParameters->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            std::printf(" Video Codec: %s. Frames: %ld.\n", szCodecName, pFormatContext->streams[i]->nb_frames);
        }
        else if (pCodecParameters->codec_type == AVMEDIA_TYPE_AUDIO)
            std::printf(" Audio Codec: %s, %d channels.\n", szCodecName, pCodecParameters->channels);
    }
    std::cout << std::endl;
    std::printf("File duration: %ld sec.\n", pFormatContext->duration / AV_TIME_BASE);

    avformat_close_input(&pFormatContext);
    avformat_free_context(pFormatContext);

    return 0;
}
