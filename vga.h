#include "types.h"
namespace myos
{
    namespace drivers
    {
        class VideoGraphicsArray
        {
            protected:
                hardwarecommunication::Port8bit miscPort;
                hardwarecommunication::Port8bit crtcIndexPort;
                hardwarecommunication::Port8bit crtcDataPort;
                hardwarecommunication::Port8bit sequencerIndexPort;
                hardwarecommunication::Port8bit sequenceerDataPort;
                hardwarecommunication::Port8bit graphicsControllerIndexPort;
                hardwarecommunication::Port8bit graphicsControllerDataPort;
                hardwarecommunication::Port8bit attributeControllerIndexPort; 
                hardwarecommunication::Port8bit attributeControllerReadPort;
                hardwarecommunication::Port8bit attributeControllerWritePort;
                hardwarecommunication::Port8bit attributeControllerResetPort;

            public:
                VideoGraphicsArray();
                virtual ~VideoGraphicsArray();

                virtual bool SupportsMode(unit32_t width,unit32_t height,unit32_t colordepth);
                virtual bool SetMode(unit32_t width,unit32_t height,unit32_t colordepth);
                virtual void PutPixel(unit32_t x,unit32_t y,unit8_t r,unit8_t g,unit8_t b);
        };       
    }

}