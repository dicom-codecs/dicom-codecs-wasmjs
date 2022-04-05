const fs = require('fs')
const dicomcodecs = require('../dist/dicomcodecswasm.js')

const readAndDecode = (filePath, codec) => {
    encodedBitStream = fs.readFileSync(filePath)
    const encodedBuffer = dicomcodecs.getEncodedBuffer(encodedBitStream.length)
    encodedBuffer.set(encodedBitStream)
    dicomcodecs.decode(codec)
    const decodedBuffer = dicomcodecs.getDecodedBuffer()
    const image = dicomcodecs.getImage()
    console.log('decoded ' + codec + ' image ' + image.width + "x" + image.height)
    image.rawBytes = decodedBuffer
    //console.log(image)
    return image
}

dicomcodecs.onRuntimeInitialized = async _ => {
    try {
        dicomcodecs.init()
        readAndDecode('../extern/dicom-codecs/extern/test-data/jpeg2000/CT1.j2k', 'openjpeg')
        readAndDecode('../extern/dicom-codecs/extern/test-data/jpegls/CT1.JLS', 'charls')
        readAndDecode('../extern/dicom-codecs/extern/test-data/jpeglossy8bit/jpeg400jfif.jpg', 'libjpeg-turbo')
        readAndDecode('../extern/dicom-codecs/extern/test-data/jpeglossy12bit/test12.jpg', 'ijg12')
    } catch (ex) {
        console.log('caught exception' + ex)
    }
}
