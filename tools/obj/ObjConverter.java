/*
 * Copyright (c) 2011 Michael Nischt
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
package org.interaction3d.assembly.tools.obj;

import java.io.BufferedReader;
import java.io.Closeable;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

import static java.lang.Float.parseFloat;
import static java.lang.Integer.parseInt;

/**
 * http://local.wasp.uwa.edu.au/~pbourke/dataformats/obj/
 * @author Michael Nischt
 */
public final class ObjConverter 
{ 
    // tmp vars for current state
    private int smoothingGroup;
    private String object;
          
    // flags
    private boolean multiple = false;
    
    private ArrayList<Mesh> meshes = new ArrayList<Mesh>();
    private Mesh mesh;
      
    
    public ObjConverter() 
    {
    }
    
    
    // <editor-fold defaultstate="collapsed" desc="convert">

    public void convert(String path)
    {
        String name = Path.trunkObj(Path.filename(path));
        
        InputStream in = Path.inputStream(path);
        try
        {
            convert(in, name);
        }
        finally
        {
            close(in);
        }
    }

    private void convert(InputStream in, String name)
    {
        try
        {
            BufferedReader reader = new BufferedReader(new InputStreamReader(in));
            convertAndClose(reader, name);
        }
        catch (IOException ex)
        {
            throw new RuntimeException(ex);
        }
    }

    private void convert(BufferedReader reader, String name) throws IOException
    {        
        smoothingGroup = 0;
        object = name;
        mesh = new Mesh(name);
                
        String line;
        while((line=reader.readLine()) != null)
        {
            line(line);
        }
        
        mesh(object);
    }

    
    private void convertAndClose(BufferedReader reader, String name) throws IOException
    {
        try
        {
            convert(reader, name);
        }
        finally
        {
            close(reader);
        }
    }    

    static private void close(Closeable c)
    {
        try
        {
            c.close();
        }
        catch (IOException e)
        {
            throw new RuntimeException(e);
        }
    }
    
    public void save(String path)
    {
        File file = Path.file(path);
        
        if(!file.isDirectory())
        {
            file.mkdirs();
        }
        
        for(Mesh next : meshes)
        {            
            next.writeTo(path);
        }
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="line">
    
    private void line(String line)
    {
        {   // get rid of comment
            int index = line.indexOf('#');
            if(index >= 0)
            {
                line = line.substring(0, index);
            }
        }
        line = line.trim();

        StringTokenizer scanner = new StringTokenizer(line);

        //empty line
        if(!scanner.hasMoreElements())
        {
            return;
        }

        String op = scanner.nextToken();


        if(op.equals("v"))
        {
            position(scanner);
        }
        else if(op.equals("vn"))
        {
            normal(scanner);
        }
        else if(op.equals("vt"))
        {
            texture(scanner);
        }
        else if(op.equals("p"))
        {
            points(scanner);
        }
        else if(op.equals("l"))
        {
            lines(scanner);
        }
        else if(op.equals("f"))
        {
            faces(scanner);
        }
        else if(op.equals("g"))
        {
            groups(scanner);
        }
        else if(op.equals("s"))
        {
            smoothingGroup(scanner.nextToken());
        }
        else if(op.equals("o"))
        {
            object(scanner.nextToken());
        }
        else if(op.equals("usemtl"))
        {
            usemtl(scanner.nextToken());
        }
        else if(op.equals("mtllib"))
        {
            mtllib(scanner);
        }
        else
        {
            //log("Unknown: " + op);
        }
    }

    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="vertices">

    private void position(StringTokenizer scanner)
    {
        // x y z (w=1)
        float[] v = new float[3];
        v[0] = parseFloat(scanner.nextToken());
        v[1] = parseFloat(scanner.nextToken());
        v[2] = parseFloat(scanner.nextToken());
                
        if(scanner.hasMoreTokens())
        {
            float w = parseFloat(scanner.nextToken());
            v[0] /= w;
            v[1] /= w;
            v[2] /= w;
        }
        mesh.v(v);
    }    

    private void texture(StringTokenizer scanner)
    {
        // u (v=0) (w=0)
        float[] texture = new float[2];
        
        float u = parseFloat(scanner.nextToken());
        if(scanner.hasMoreTokens())
        {
            float v = parseFloat(scanner.nextToken());
            //if(scanner.hasMoreTokens())
            //{
            //    float w = parsefloat(scanner.nextToken());
            //    texture = new float[3];
            //    texture[2] = w;
            //}
            //else
            //{
            //    texture = new float[2];
            //}
            texture[1] = v;
        }
        //else
        //{
        //    texture = new float[1];
        //}
        texture[0] = u;
        
        mesh.vt(texture);
    }

    private void normal(StringTokenizer scanner)
    {
        // i j k
        float[] normal =
        {
            parseFloat(scanner.nextToken()),
            parseFloat(scanner.nextToken()),
            parseFloat(scanner.nextToken())
        };

        mesh.vn(normal);
    }

    // </editor-fold>
    
    // <editor-fold defaultstate="collapsed" desc="primitives">

    private void points(StringTokenizer scanner)
    {
        // v1 v2 v3 . . .
        List<int[]> points = new ArrayList<int[]>();
        while (scanner.hasMoreTokens())
        {
            int p = parseInt(scanner.nextToken());
            points.add(new int[] { p });
        }
        mesh.p(points);
    }

    private void lines(StringTokenizer scanner)
    {
        // v1/vt1 v2/vt2 v3/vt3 . . .
        // can be v/t or v
        List<int[]> lines = new ArrayList<int[]>();
        while(scanner.hasMoreTokens())
        {
            int p,t;
            {
                String vert = scanner.nextToken();
                int split = vert.indexOf('/');
                if(split < 0) split = vert.length();

                p = parseInt(vert.substring(0, split++));
                t = (split < vert.length()) ? t = parseInt(vert.substring(split)) : 0;
            }
            lines.add(new int[] { p, t});
        }
        mesh.l(lines);

    }

    private void faces(StringTokenizer scanner)
    {
        // v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 . . .
        // can be v/t/n or v/t or v//n or v

        List<int[]> face = new ArrayList<int[]>();
        while(scanner.hasMoreTokens())
        {
            int p,t,n;
            {
                String vert = scanner.nextToken();
                int split1 = vert.indexOf('/');
                if(split1 < 0) split1 = vert.length();
                int split2 = vert.indexOf('/', split1+1);
                if(split2 < 0) split2 = vert.length();


                p = parseInt(vert.substring(0, split1++));
                t = (split1 < split2) ? parseInt(vert.substring(split1, split2)) : 0;
                split2++;
                n = (split2 < vert.length()) ?  parseInt(vert.substring(split2)) : 0;                
            }

            face.add( new int[] {p, t, n} );
        }
        mesh.f(face, smoothingGroup);
    }
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="misc">

    private void mtllib(StringTokenizer scanner)
    {
        // filename1 filename2 . . .
        //List<String> list = new ArrayList<String>();
        //while(scanner.hasMoreTokens())
        //{
        //    list.add(scanner.nextToken());
        //}
        //log("ignored: mtllib filename1 filename2 ...");
    }

    private void usemtl(String material)
    {
        mesh.usemtl(material);
    }

    private void smoothingGroup(String group)
    {
        // group_number or 0 or 'off'
        smoothingGroup = (group.equalsIgnoreCase("off"))
                       ? 0
                       : parseInt(group);
    }

    private void object(String group)
    {
        // object_name
        if(multiple)
        {
            mesh(object = group);
        }
    }

    private void groups(StringTokenizer scanner)
    {
        // (group_name1=default) (group_name2) . . .
        //log("Groups (g) are not supported");
    }

    // </editor-fold>

    private void mesh(String name)
    {
        meshes.add(mesh);
        mesh = mesh.next(name);
    }
        
    // <editor-fold defaultstate="collapsed" desc="main">

    public static void main( String... args ) throws Exception
    {
        if(args.length == 0)
        {
            System.out.println("Usage: <source-file.obj> <output-directory>");
            return;
        }
        
        String src = args[0];
        String dst;
        if(args.length > 1)
        {
            dst = args[1];
        }
        else
        {
            dst = System.getProperty("user.dir");
        }
        
        ObjConverter converter = new ObjConverter();
        converter.convert(src);
        converter.save(dst);
    }    
    
    // </editor-fold>

}