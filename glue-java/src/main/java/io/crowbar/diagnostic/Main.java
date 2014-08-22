package io.crowbar.diagnostic;

import io.crowbar.diagnostic.runners.*;
import io.crowbar.diagnostic.algorithms.*;
import io.crowbar.diagnostic.spectrum.*;
import io.crowbar.diagnostic.spectrum.unserializers.*;
import io.crowbar.messages.*;

import flexjson.JSONSerializer;
import flexjson.JSONDeserializer;
import java.util.Scanner;
import java.util.Random;
import java.util.List;
import java.util.ArrayList;


public class Main {
    static List<Double> randomizeScores(int numNodes){
        List<Double> l = new ArrayList<Double>();
        Random r = new Random();
        while(numNodes-- > 0) {
            l.add(r.nextDouble());
        }
        return l;
    }

    static Tree randomizeTree(int numNodes){
        EditableTree t = new EditableTree("asd");
        Random r = new Random();

        while(numNodes-- > 0) {
            t.addNode(""+r.nextInt(), r.nextInt(t.size()));
        }
        return t;
    }

    static void foo1() {
        Spectrum s = HitSpectrumUnserializer.unserialize(new Scanner("10 9 0 1 0 0 0 0 0 0 0 0 0.0 0 0 0 1 0 0 0 0 0 0 0.0 1 0 0 0 0 1 0 0 0 0 0.0 0 0 0 0 0 0 0 1 0 0 0.0 0 0 0 0 0 0 0 0 1 0 0.0 0 0 1 0 0 0 0 0 0 0 1.0 0 0 0 0 1 0 0 0 0 0 1.0 0 0 0 0 0 0 1 0 0 0 1.0 0 0 0 0 0 0 0 0 0 1 1.0"));
        TransactionFactory tf = new TransactionFactory();

        DiagnosticSystemFactory j = new DiagnosticSystemFactory();


        j.addGenerator(new SingleFaultGenerator());
        j.addGenerator(new MHSGenerator());


        j.addRanker(new SimilarityRanker(SimilarityRanker.Type.OCHIAI));
        j.addConnection(0, 0);
        j.addConnection(1, 0);

        j.addRanker(new FuzzinelRanker());
        j.addConnection(1, 1);


        try {
            JNARunner runner = new JNARunner();

            System.out.println("------ Inside JNA --------");
            DiagnosticReport dr = runner.run(j.create(), s);
            System.out.println("------ Inside JNA --------");

            System.out.println("DiagnosticReport After deserialization: ");
            System.out.println(new JSONSerializer().deepSerialize(dr));
        }
        catch (Throwable e) {e.printStackTrace();}
    }

    public static void foo2() {
        Scanner terminalInput = new Scanner(System.in);
        while(true) {
            try {
                String s = terminalInput.nextLine();
                DiagnosticReport dr = new JSONDeserializer<DiagnosticReport>().deserialize(s);

                System.out.println(new JSONSerializer().exclude("*.class").deepSerialize(dr));
            }
            catch(flexjson.JSONException e) {
                e.printStackTrace();
            }
            catch(java.lang.ClassCastException e) {
                e.printStackTrace();
            }
        }
    }


    public static void foo3() {

        String jsonRequest = Messages.serialize(
            VisualizationMessages.issueRequest(
                randomizeTree(10),
                randomizeScores(10)));

        System.out.println(jsonRequest);
    }
    public static void main (String[] args) {
//        foo1();
//        foo2();
        foo3();
    }
}