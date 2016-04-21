using UnityEngine;
using System.Collections;

public class CharacterLoader : MonoBehaviour {

	private int currentCharacter;

	// Use this for initialization
	void Start () {
		int currentCharacter = LoadNewCharacter.currentCharacterPlaying;

		if (currentCharacter == 1)
		{
			GameObject instance = Instantiate(Resources.Load("Name of gameObject to load", typeof(GameObject))) as GameObject;
			
		}

		if (currentCharacter == 2)
		{
			GameObject instance = Instantiate(Resources.Load("Name of second gameObject to load", typeof(GameObject))) as GameObject;
			
		}		
	}
}
