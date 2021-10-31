class Device {
    constructor(name, topic, Port, callback) {
        this.name = name
        this.type = "device"
        this.topic = topic
        this.port = Port
        this.callback = callback
        //this.val = this.startDevice()

        Port.on('readable', function () {
            let data  = Port.read()

            if(data != null){
                console.log("read data: " + data.toString())
            }
            else{
                console.log("Null")
            }
            //console.log(this.name + ' Data:', Port.read())
          })
    }
    
    tunrON() {
        console.log(this.name + " ON")
        this.sendDevice(this.topic,1)
    }

    tunrOFF() {
        console.log(this.name + " OFF")
    }

    sendDevice(topic, payload) {
        var foo = {
            "topic": topic,
            "payload": payload
        }
        foo = JSON.stringify(foo) + "\n"
        this.port.write(foo, function (err) {
            if (err) {
                return console.log('Error on write: ', err.message)
            }
            //console.log('message written')
        })
        //console.log('Data:', port.read())
    }

    readValue(){
       // this.sendDevice(this.topic , 1)
        //console.log(this.name + ' Data:', port.read().toString())
    }

}
module.exports = Device