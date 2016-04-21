using UnityEngine;
using System.Collections;
using System.IO.Ports;
using System.Threading;

public class LoadNewCharacter : MonoBehaviour
{
	//serialPort
	SerialPort sp;
	private int rfidInt;
	static public int currentCharacterPlaying;

	// Use this for initialization
	void Start ()
	{
		//SerialPort Setup Connection
		sp = new SerialPort ("COM3", 9600);  // use /dev/tty.usbmodem1411 for mac usb connection
		sp.Open ();
		sp.ReadTimeout = 16;

		currentCharacterPlaying = 1; //Use this for loading an object at start
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (sp.IsOpen) 
		{
			try {
				LoadCharacter(sp.ReadByte()); //pass in the id from the rfid/arduino setup
			} catch (System.Exception){}
		}
	}
		
	void LoadCharacter (int loadChar)
	{
		rfidInt = loadChar;
	}	
}
