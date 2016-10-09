package com.mio.newdynamicc;

/**
 * Created by mio4kon on 16/10/8.
 */

public class CUtils {


    static {
        System.loadLibrary("login-lib");
    }

    public static native int loginOne(byte[] username, byte[] password);
    public static native int loginTwo(String username, String password);
}
