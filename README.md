Resource:

https://gitlab.xiph.org/xiph/vorbis  
https://gitlab.xiph.org/xiph/vorbis-tools  
https://lists.xiph.org/pipermail/vorbis/2002-August/021175.html  
https://lists.xiph.org/pipermail/vorbis/2002-August/021175.html  
https://www.xiph.org/vorbis/doc/libvorbis/vorbis_analysis_buffer.html  
https://www.xiph.org/vorbis/doc/libvorbis/vorbis_analysis_blockout.html  
https://www.xiph.org/vorbis/doc/libvorbis/vorbis_block.html  
https://www.xiph.org/ogg/doc/libogg/reference.html  
https://www.xiph.org/ogg/doc/libogg/ogg_stream_pageout.html  
https://www.xiph.org/vorbis/doc/libvorbis/reference.html  

Build: ./build.sh  
Run test: ./test.sh  

Working oggenc:   
`cd data`  
`(cat test-light.wav 0.5s-silence 0.5s-silence && sleep 5) | oggenc --max-bitrate 100  --min-bitrate 75 - > b.ogg`  
`(cat a.wav 0.5s-silence 0.5s-silence 0.5s-silence && sleep 2) | oggenc --min-bitrate 75 -  | ogg123 -`

Notice:
- fread(readbuffer, 1, READ * 2, stdin): read until enough byte or end of stream:
16:23:24 2048
16:23:24 2048
16:23:24 2048
16:23:30 812
16:23:30 0
FINISH

Cut file:
`dd if=test-a.wav of=6144.wav bs=1 count=6144`
