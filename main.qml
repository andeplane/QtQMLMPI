import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QMPI 1.0

Window {
    id: windowRoot
    visible: true

    Column {
        TextField {
            id: textBox
            text: "Message"
        }
        Button {
            text: "Send to all"
            onClicked: {
                console.log("MPI: "+mpi)
                mpi.sendMessageToAll(textBox.text)
            }
        }
        Button {
            text: "Send to each"
            onClicked: {
                mpi.sendMessageToEach(textBox.text)
            }
        }
        Button {
            text: "Quit"
            onClicked: {
                mpi.quit()
                Qt.quit()
            }
        }
    }
}

