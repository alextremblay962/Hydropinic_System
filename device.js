class Device {
    constructor(name, topic, port, callback) {
        this.name = name
        this.type = "device"
        this.topic = topic
        this.port = port
        this.callback = callback
        //this.val = this.startDevice()

        // this.port.on('readable', function () {
        //     console.log(this.name + ' Data:', port.read())
        //   })

    }
    tunrON() {
        console.log(this.name + " ON")
        this.sendDevice("hydro/light1",1)

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
        this.sendDevice(this.topic , 1)
        
    }



}
module.exports = Device