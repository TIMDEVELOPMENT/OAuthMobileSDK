package timsdk.app.tim.com.br.apptimoam;

import android.content.Context;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;

/**
 * Created by mobility on 9/2/15.
 */
public final class InternalStorage{

    private InternalStorage() {}

    public static void writeObject(Context context, String key, Object object) throws IOException {
        FileOutputStream fos = context.openFileOutput(key, Context.MODE_PRIVATE);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        AppendingObjectOutputStream aois=new AppendingObjectOutputStream(oos);
        aois.writeObject(object);
        oos.close();
        aois.close();
        fos.close();
    }
    public static void writeObject(Context context, String key, String object) throws IOException {
        FileOutputStream fos = context.openFileOutput(key, Context.MODE_PRIVATE);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        AppendingObjectOutputStream aois=new AppendingObjectOutputStream(oos);
        aois.writeChars(object);
        oos.close();
        aois.close();
        fos.close();
    }


    public static Object readObject(Context context, String key) throws IOException,
            ClassNotFoundException {
        FileInputStream fis = context.openFileInput(key);
        ObjectInputStream ois = new ObjectInputStream(fis);
        Object object = ois.readObject();
        fis.close();
        ois.close();
        return object;
    }


}