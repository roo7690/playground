/*
	Auteur : Max Bleriot Mba Fossi - 2417938 : Roosevelt Sonfack Ngoune - 2464064
	Date : 04/21/2026
	Cr�� le : 04/08/2026
*/

import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    width: 500
    height: 600
    visible: true
    title: "Friend Chess"

    Text {
        id: titre
        x: 180
        y: 14
        width: 141
        height: 19
        color: "#213e24"
        text: "Welcome to Chess-Master"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        font.styleName: "Gras"
        font.family: "Courier"
    }

    property variant possibleMoves: []
    property int selectedIndex: -1  // -1 signifie "aucune s�lection"
    property int refreshCounter: 0
    
    Grid {
        id: grid
        x: 10
        y: 80
        width: 480
        height: 480
        //padding: 1
        //paddingTop: 1
        spacing: 1
        rows: 8
        columns: 8

        Repeater {
            model: 64            
            Rectangle {
                width: grid.width / 8
                height: grid.height / 8
               
                // Math : index % 8 donne la colonne, Math.floor(index / 8) donne la ligne
                property color baseColor: (Math.floor(index / 8) + (index % 8)) % 2 === 0 ? "#FCFBF4" : "#185E3F"
    
                // D�terminer si cette case fait partie des mouvements possibles
                property bool isHighlighted: possibleMoves.indexOf(index) !== -1

                color: isHighlighted ? "#f1c40f" : baseColor
                 
                Text {
                    text: index // Utile pour d�boguer tes positions au d�but
                    anchors.centerIn: parent
                    color: "red"
                    opacity: 0.3
                }

                Image {
                   width: parent.width - 10  // 5px de chaque c�t�
                    height: parent.height - 10
                    anchors.centerIn: parent  
                    property string path: echiquier.getPionImage(index)    
                    source: {
                        refreshCounter; // force le binding � se recalculer
                        return echiquier.getPionImage(index);
                    }                    
                    // L'image n'est affich�e que si le chemin n'est pas vide ("")
                    visible: path !== ""
                    fillMode: Image.PreserveAspectFit
                }
                Connections {
                    target: echiquier
                    function onCaseUpdate() {
                        refreshCounter++; // On change le compteur
                        // On demande aussi de recalculer les mouvements possibles pour la nouvelle case
                        if (selectedIndex !== -1) {
                            possibleMoves = echiquier.getPossibilitePion(selectedIndex);

                        }
                    }
                }
                // Le "Listener" pour chaque case
                MouseArea {
                    anchors.fill: parent // Prend toute la place de la case
                    hoverEnabled: true   // Permet de d�tecter le survol

                    onClicked: {
                        // Calcul des coordonn�es d'�checs
                        let row = Math.floor(index / 8);
                        let col = index % 8;

                        console.log("Case cliqu�e : Ligne " + row + ", Colonne " + col);
                        if (possibleMoves.indexOf(index) !== -1) {
                            // On demande au C++ d'ex�cuter le mouvement r�el
                            echiquier.deplacerPion(selectedIndex, index);
            
                            // On r�initialise tout apr�s le mouvement
                            selectedIndex = -1;
                            possibleMoves = [];
                        }                               
                        else {
                            // On m�morise l'index de d�part
                            selectedIndex = index;                            
                            possibleMoves = echiquier.getPossibilitePion(index);
                        }	                                                                        
                       
                    }

                    // Effet visuel au survol
                    onEntered: parent.border.color = "blue"
                    onExited: parent.border.color = "transparent"
                }
            }
        }
    }    

}
