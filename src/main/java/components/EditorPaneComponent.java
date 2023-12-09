/**
 * Copyright (C) 2013, 2014 Johannes Taelman
 *
 * This file is part of Axoloti.
 *
 * Axoloti is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * Axoloti is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Axoloti. If not, see <http://www.gnu.org/licenses/>.
 */
package components;
import axoloti.Theme;
import axoloti.utils.Constants;
import java.awt.Dimension;
import javax.swing.JEditorPane;

/**
 *
 * @author Johannes Taelman, sebiik
 */
public class EditorPaneComponent extends JEditorPane {


    public EditorPaneComponent() {
        setContentType("text/html");
        setMinimumSize(new Dimension(12,13));
        setFont(Constants.FONT);
        setBackground(Theme.getCurrentTheme().Object_Default_Background);
        setForeground(Theme.getCurrentTheme().Object_Label_Text);
        setEditable(false);
        setFocusable(false);
    }

    public EditorPaneComponent(String text) {
        setContentType("text/html");
        setText(text);
        setMinimumSize(new Dimension(12,13));
        setFont(Constants.FONT);
        setBackground(Theme.getCurrentTheme().Object_Default_Background);
        setForeground(Theme.getCurrentTheme().Object_Label_Text);
        setEditable(false);
        setFocusable(false);
    }
}