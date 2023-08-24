Resource:

https://gitlab.xiph.org/xiph/vorbis
https://gitlab.xiph.org/xiph/vorbis-tools
https://lists.xiph.org/pipermail/vorbis/2002-August/021175.html
https://lists.xiph.org/pipermail/vorbis/2002-August/021175.html


Build: ./build.sh  
Run test: ./test.sh  

Working oggenc:   
`cd data`  
`(cat test-light.wav 0.5s-silence 0.5s-silence && sleep 5) | oggenc --max-bitrate 100  --min-bitrate 75 - > b.ogg`  
