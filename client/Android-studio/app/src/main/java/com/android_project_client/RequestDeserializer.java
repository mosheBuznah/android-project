package com.android_project_client;

import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

public class RequestDeserializer {
    public static JSONObject getJsonData(byte[] messageFromServer)
    {
        int code = getCode(messageFromServer);
        int sizeMessage = getSizeMessage(messageFromServer);

        String jsonStr = "";
        for(int i = 0; i < sizeMessage; i++)
        {
            jsonStr = jsonStr + String.valueOf(messageFromServer[5+i]);
        }

        JSONObject jsonObject;
        try {
            jsonObject = new JSONObject(jsonStr);
        }catch (JSONException err){
            Log.d("Error", err.toString());
            return null;
        }

        return jsonObject;
    }

    public static byte getCode(byte[] messageFromServer)
    {
        return messageFromServer[0];
    }

    public static int getSizeMessage(byte[] messageFromServer)
    {
        int retVal = 0;

        retVal |= (int)messageFromServer[1] << 24;
        retVal |= (int)messageFromServer[2] << 16;
        retVal |= (int)messageFromServer[3] << 8;
        retVal |= messageFromServer[4];

        return retVal;
    }
}

