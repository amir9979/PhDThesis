package io.crowbar.diagnosis.spectra;

public class HitSpectraSerializer {
    public static String serialize (Spectra< ? extends Activity, ? , ? > spectra) {
        int numComp = spectra.getNumComponents();
        int numTran = spectra.getNumTransactions();
        StringBuilder str = new StringBuilder();


        str.append(numComp);
        str.append(" ");
        str.append(numTran);
        str.append("\n");

        for (Transaction t : spectra) {
            str.append(serialize(t, numComp));
            str.append("\n");
        }

        return str.toString();
    }

    public static String serialize (Transaction< ? extends Activity, ? > transaction,
                                    int numComponents) {
        StringBuilder str = new StringBuilder();
        int i = 0;


        for (i = 0; i < transaction.size(); i++) {
            str.append(transaction.get(i).isActive() ? "1" : "0");
            str.append(" ");
        }

        for (; i < numComponents; i++) {
            str.append(0);
            str.append(" ");
        }

        str.append(transaction.getError());
        str.append(" ");
        str.append(transaction.getConfidence());

        return str.toString();
    }
}