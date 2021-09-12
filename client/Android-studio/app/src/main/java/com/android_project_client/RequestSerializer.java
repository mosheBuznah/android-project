package com.android_project_client;

public class RequestSerializer {
   public static byte[] create_message(byte code, String msg)
   {
       int size_message = msg.length();
       byte[] message = new byte[5 + size_message + 1]; // code + 4 bytes of message length + message itself + null
       message[0] = code;
       message[1] = (byte)(size_message >> 24);
       message[2] = (byte)((size_message >> 16) | (~0 >> 24));
       message[3] = (byte)((size_message >> 8) | (~0 >> 24));
       message[4] = (byte)(size_message | (~0 >> 24));

       char[] msg_chars = msg.toCharArray();
       int index = 0;
       for (char c: msg_chars) {
           message[5 + index] = (byte)c;
           index++;
       }

       return message;
   }


}
