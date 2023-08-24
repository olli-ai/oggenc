#include <stdio.h>
#include <vorbis/vorbisenc.h>

// unsigned long long factorial(unsigned int n)
// {
//     if (n == 0 || n == 1)
//     {
//         return 1;
//     }
//     else
//     {
//         return n * factorial(n - 1);
//     }
// }

// int fdfdsndfsnfdsanfd()
// {
//     vorbis_info vi;
//     // Set up Vorbis encoder settings
//     vorbis_info_init(&vi);
//     if (vorbis_encode_init_vbr(&vi, 2, 44100, 0.4f) != 0)
//     {
//         fprintf(stderr, "Error initializing Vorbis encoder\n");
//         return 1;
//     }

//     // Open a file for writing encoded data
//     FILE *outputFile = fopen("output.ogg", "wb");
//     if (!outputFile)
//     {
//         fprintf(stderr, "Error opening output file\n");
//         return 1;
//     }

//     // Initialize the Vorbis encoder
//     vorbis_dsp_state vd;
//     vorbis_block vb;
//     vorbis_analysis_init(&vd, &vi);
//     vorbis_block_init(&vd, &vb);

//     // Simulated PCM buffer (replace this with your actual PCM data)
//     short pcm_buffer[4096]; // Example buffer size
//     float **pcm = vorbis_analysis_buffer(&vd, 4096);
//     // Read WAV data from stdin

//     size_t read_samples;
//     while ((read_samples = fread(pcm_buffer, sizeof(short), 4096, stdin)) > 0)
//     {
//         for (size_t i = 0; i < read_samples; ++i)
//         {
//             pcm[0][i] = pcm_buffer[i] / 32768.0f;
//             pcm[1][i] = pcm_buffer[i] / 32768.0f;
//         }

//         vorbis_analysis_wrote(&vd, read_samples);

//         ogg_stream_state os;
//         ogg_page og;
//         ogg_packet op;

//         ogg_stream_init(&os, 12345);
//         while (vorbis_analysis_blockout(&vd, &vb) == 1)
//         {
//             vorbis_analysis(&vb, NULL);
//             vorbis_bitrate_addblock(&vb);

//             while (vorbis_bitrate_flushpacket(&vd, &op))
//             {
//                 ogg_stream_packetin(&os, &op);
//                 while (ogg_stream_pageout(&os, &og))
//                 {
//                     // Write the Ogg page data to an output file
//                     fwrite(og.header, 1, og.header_len, outputFile);
//                     fwrite(og.body, 1, og.body_len, outputFile);
//                 }
//             }
//         }

//         ogg_stream_clear(&os);
//     }

//     vorbis_block_clear(&vb);
//     vorbis_dsp_clear(&vd);

//     return 0;
// }

void enc1(const char *inputWavFile, const char *outputOggFile)
{
    // Set up Vorbis encoder settings
    vorbis_info vi;
    vorbis_info_init(&vi);
    if (vorbis_encode_init_vbr(&vi, 1, 22050, 0.4f) != 0)
    {
        fprintf(stderr, "Error initializing Vorbis encoder\n");
        return;
    }

    // Initialize the Vorbis encoder
    vorbis_dsp_state vd;
    vorbis_block vb;
    vorbis_analysis_init(&vd, &vi);
    vorbis_block_init(&vd, &vb);

    FILE *inputFile = fopen(inputWavFile, "rb");
    if (!inputFile)
    {
        fprintf(stderr, "Error opening input WAV file\n");
        return;
    }

    FILE *outputFile = fopen(outputOggFile, "wb");
    if (!outputFile)
    {
        fprintf(stderr, "Error opening output OGG file\n");
        fclose(inputFile);
        return;
    }

    short pcm_buffer[4096]; // Example buffer size
    float **pcm = vorbis_analysis_buffer(&vd, 4096);

    size_t read_samples;
    while ((read_samples = fread(pcm_buffer, sizeof(short), 4096, inputFile)) > 0)
    {
        printf("111 %ld\n", read_samples);
        for (size_t i = 0; i < read_samples; ++i)
        {
            pcm[0][i] = pcm_buffer[i] / 32768.0f;
        }

        vorbis_analysis_wrote(&vd, read_samples);

        ogg_stream_state os;
        ogg_page og;
        ogg_packet op;

        ogg_stream_init(&os, 12345);
        while (vorbis_analysis_blockout(&vd, &vb) == 1)
        {
            vorbis_analysis(&vb, NULL);
            vorbis_bitrate_addblock(&vb);

            while (vorbis_bitrate_flushpacket(&vd, &op))
            {
                ogg_stream_packetin(&os, &op);
                while (ogg_stream_pageout(&os, &og))
                {
                    fwrite(og.header, 1, og.header_len, outputFile);
                    fwrite(og.body, 1, og.body_len, outputFile);
                }
            }
        }

        ogg_stream_clear(&os);
    }

    fclose(outputFile);
    fclose(inputFile);

    vorbis_block_clear(&vb);
    vorbis_dsp_clear(&vd);
}
